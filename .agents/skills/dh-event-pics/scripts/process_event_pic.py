import sys
import os
import urllib.request
import urllib.parse
import json
import io
from PIL import Image, ImageOps

HEADERS = {
    'User-Agent': 'DHModdingTool/1.0 (https://github.com/kamika888; darkesthourmod@gmail.com)'
}

def resolve_wikimedia_thumb(file_or_url, width=800):
    """If file_or_url is a Wikimedia Commons File title or wiki URL, resolve to 800px edge thumbnail."""
    title = None
    if file_or_url.startswith("File:"):
        title = file_or_url
    elif "commons.wikimedia.org/wiki/File:" in file_or_url:
        title = "File:" + file_or_url.split("commons.wikimedia.org/wiki/File:")[1].split("?")[0]
        title = urllib.parse.unquote(title)
        
    if title:
        api_url = f"https://commons.wikimedia.org/w/api.php?action=query&titles={urllib.parse.quote(title)}&prop=imageinfo&iiprop=url&iiurlwidth={width}&format=json"
        req = urllib.request.Request(api_url, headers=HEADERS)
        try:
            with urllib.request.urlopen(req, timeout=10) as r:
                data = json.loads(r.read().decode('utf-8'))
                pages = data.get('query', {}).get('pages', {})
                for p in pages.values():
                    info = p.get('imageinfo', [])
                    if info:
                        return info[0].get('thumburl') or info[0].get('url')
        except Exception as e:
            print(f"Warning: Failed to resolve Wikimedia API thumb for {title}: {e}")
            
    return file_or_url

def process_image(image_src, output_path, template_path, is_decision=False, crop_y=0.5):
    # crop_y: 0.0 = crop from very top, 0.5 = center (default), 1.0 = crop from bottom
    if os.path.exists(image_src):
        with open(image_src, 'rb') as f:
            data = f.read()
    else:
        resolved_url = resolve_wikimedia_thumb(image_src)
        req = urllib.request.Request(resolved_url, headers=HEADERS)
        with urllib.request.urlopen(req, timeout=15) as response:
            data = response.read()
    
    img = Image.open(io.BytesIO(data))
    if img.mode != 'RGB':
        img = img.convert('RGB')
    
    # Target specs
    if is_decision:
        target_size = (224, 48)
        template_filename = 'decision_template.png'
    else:
        target_size = (400, 232)
        template_filename = 'template.png'
    
    # Resize and crop with configurable vertical crop position
    w, h = img.size
    target_w, target_h = target_size
    target_aspect = target_w / target_h
    source_aspect = w / h

    if source_aspect > target_aspect:
        # Source wider than target: crop sides, keep full height
        new_w = int(h * target_aspect)
        left = (w - new_w) // 2
        img = img.crop((left, 0, left + new_w, h))
    else:
        # Source taller/narrower: crop height with configurable vertical position
        new_h = int(w / target_aspect)
        max_offset = max(0, h - new_h)
        top_offset = int(max_offset * crop_y)
        img = img.crop((0, top_offset, w, top_offset + new_h))

    img = img.resize(target_size, Image.Resampling.LANCZOS)
    
    # Overlay template if exists
    template_file = os.path.join(os.path.dirname(template_path), template_filename)
    if os.path.exists(template_file):
        template = Image.open(template_file).convert('RGBA')
        if template.size != target_size:
            template = template.resize(target_size)
        
        img = img.convert('RGBA')
        img.paste(template, (0, 0), template)
    
    # Save as BMP
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    img.convert('RGB').save(output_path, 'BMP')
    print(f"Successfully processed and saved to {output_path} ({target_size[0]}x{target_size[1]}) [crop_y={crop_y}]")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python process_event_pic.py <URL|FILE_TITLE|LOCAL_PATH> <OUTPUT_NAME_NO_EXT> [--decision] [--crop-y 0.0-1.0]")
        print("  --crop-y: vertical crop position (0.0=top, 0.5=center/default, 1.0=bottom)")
        sys.exit(1)
    
    src = sys.argv[1]
    output_name = sys.argv[2]
    is_decision = "--decision" in sys.argv
    crop_y = 0.5
    for i, arg in enumerate(sys.argv):
        if arg == "--crop-y" and i + 1 < len(sys.argv):
            crop_y = float(sys.argv[i + 1])
    
    # Standard paths for this project
    workspace_root = os.getcwd()
    output_path = os.path.join(workspace_root, 'gfx', 'events_pics', f"{output_name}.bmp")
    template_path = os.path.join(workspace_root, 'gfx', 'events_pics', 'template.png')
    
    process_image(src, output_path, template_path, is_decision, crop_y=crop_y)
