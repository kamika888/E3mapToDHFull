#!/usr/bin/env python3
"""
Darkest Hour Portrait Processing Tool
Processes source images into 36x50 8-bit indexed palette BMP portraits with 1px white border.
"""

import sys
import os
import urllib.request
import json
import ssl
import time
import argparse
from PIL import Image, ImageOps
import numpy as np

ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36'
}

def get_commons_url(file_title):
    url = f"https://commons.wikimedia.org/w/api.php?action=query&titles={urllib.parse.quote(file_title)}&prop=imageinfo&iiprop=url|size&iiurlwidth=800&format=json"
    req = urllib.request.Request(url, headers=headers)
    with urllib.request.urlopen(req, context=ctx, timeout=10) as resp:
        data = json.loads(resp.read().decode('utf-8'))
        pages = data['query']['pages']
        for pid, page in pages.items():
            if 'imageinfo' in page:
                info = page['imageinfo'][0]
                return info.get('thumburl') or info.get('url')
    return None

def process_portrait(source_input, pic_id, crop_box_pct=None, output_dir="gfx/interface/pics", ref_bmp="gfx/interface/pics/MS355.bmp"):
    os.makedirs(output_dir, exist_ok=True)
    
    # Sourcing image
    if source_input.startswith("http://") or source_input.startswith("https://"):
        img_url = source_input.split('?')[0]
        req = urllib.request.Request(img_url, headers=headers)
        with urllib.request.urlopen(req, context=ctx, timeout=15) as resp:
            src = Image.open(resp).convert("RGB")
    elif source_input.startswith("File:") or source_input.startswith("file:"):
        img_url = get_commons_url(source_input)
        if not img_url:
            raise ValueError(f"Could not resolve Wikimedia Commons title: {source_input}")
        img_url = img_url.split('?')[0]
        req = urllib.request.Request(img_url, headers=headers)
        with urllib.request.urlopen(req, context=ctx, timeout=15) as resp:
            src = Image.open(resp).convert("RGB")
    elif os.path.exists(source_input):
        src = Image.open(source_input).convert("RGB")
    else:
        raise FileNotFoundError(f"Source file or URL not found: {source_input}")

    w, h = src.size
    
    # Apply face crop (targeting 60-90% face composition fill)
    if crop_box_pct:
        l, t, r, b = crop_box_pct
        left = int(w * l)
        top = int(h * t)
        right = int(w * r)
        bottom = int(h * b)
        src = src.crop((left, top, right, bottom))
        w, h = src.size

    target_w, target_h = 34, 48
    src_aspect = w / h
    target_aspect = target_w / target_h

    if src_aspect > target_aspect:
        new_h = h
        new_w = int(h * target_aspect)
        offset_x = (w - new_w) // 2
        src = src.crop((offset_x, 0, offset_x + new_w, h))
    else:
        new_w = w
        new_h = int(w / target_aspect)
        offset_y = int((h - new_h) * 0.15)
        src = src.crop((0, offset_y, w, offset_y + new_h))

    src_resized = src.resize((target_w, target_h), Image.Resampling.LANCZOS)

    # Reference palette matching MS355.bmp
    if os.path.exists(ref_bmp):
        ref_img = Image.open(ref_bmp)
        ref_palette = ref_img.getpalette()
        quantized = src_resized.quantize(palette=ref_img)
    else:
        palette = []
        for i in range(256):
            palette.extend([i, i, i])
        ref_palette = palette
        quantized = src_resized.convert("L").quantize(colors=256)

    # Paste into 36x50 frame with 1px white outline (index 255)
    canvas = Image.new("P", (36, 50), 255)
    canvas.putpalette(ref_palette)
    canvas.paste(quantized, (1, 1))

    if not pic_id.lower().endswith(".bmp"):
        pic_id += ".bmp"
    
    output_path = os.path.join(output_dir, pic_id)
    canvas.save(output_path, format="BMP")
    print(f"Successfully generated portrait: {output_path} (36x50 Mode P with 1px outline)")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process minister/leader portrait for Darkest Hour")
    parser.add_argument("source", help="Image URL, local file path, or Wikimedia File title (e.g. 'File:Example.jpg')")
    parser.add_argument("pic_id", help="Target filename/ID (e.g. MS357 or MS357.bmp)")
    parser.add_argument("--crop", nargs=4, type=float, metavar=('LEFT', 'TOP', 'RIGHT', 'BOTTOM'),
                        help="Normalized crop bounding box [0.0..1.0] for face framing (60-90%% face area)")
    parser.add_argument("--outdir", default="gfx/interface/pics", help="Output directory (default: gfx/interface/pics)")
    
    args = parser.parse_args()
    process_portrait(args.source, args.pic_id, crop_box_pct=args.crop, output_dir=args.outdir)
