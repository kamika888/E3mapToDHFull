import sys
import os
import urllib.request
import io
from PIL import Image, ImageOps

def process_image(image_url, output_path, template_path, is_decision=False):
    # Download
    req = urllib.request.Request(image_url, headers={
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36'
    })
    with urllib.request.urlopen(req) as response:
        data = response.read()
    
    img = Image.open(io.BytesIO(data))
    
    # Target specs
    if is_decision:
        target_size = (224, 48)
        template_filename = 'decision_template.png'
    else:
        target_size = (400, 232)
        template_filename = 'template.png'
    
    # Resize and crop (maintain aspect ratio)
    img = ImageOps.fit(img, target_size, Image.Resampling.LANCZOS)
    
    # Overlay template if exists
    template_path = os.path.join(os.path.dirname(template_path), template_filename)
    if os.path.exists(template_path):
        template = Image.open(template_path).convert('RGBA')
        if template.size != target_size:
            template = template.resize(target_size)
        
        img = img.convert('RGBA')
        img.paste(template, (0, 0), template)
    
    # Save as BMP
    img.convert('RGB').save(output_path, 'BMP')
    print(f"Successfully processed and saved to {output_path}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python process_event_pic.py <URL> <OUTPUT_NAME_NO_EXT> [--decision]")
        sys.exit(1)
    
    url = sys.argv[1]
    output_name = sys.argv[2]
    is_decision = "--decision" in sys.argv
    
    # Standard paths for this project
    workspace_root = os.getcwd()
    output_path = os.path.join(workspace_root, 'gfx', 'events_pics', f"{output_name}.bmp")
    template_path = os.path.join(workspace_root, 'gfx', 'events_pics', 'template.png')
    
    process_image(url, output_path, template_path, is_decision)
