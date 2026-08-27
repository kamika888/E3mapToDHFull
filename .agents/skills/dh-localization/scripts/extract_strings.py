#!/usr/bin/env python3
"""
Extract string literals and check localization keys in Darkest Hour event files.
Usage:
    python extract_strings.py <event_file_path> [--csv-dir <config_dir>] [--json]
"""
import os, sys, glob, re, json, argparse

# Standard engine keys that should not be flagged as missing literals
STANDARD_ENGINE_KEYS = {
    'AI_EVENT', 'ACTION_NAME_OK', 'ACTION_NAME_ACCEPT', 'ACTION_NAME_DECLINE',
    'ACTION_NAME_DAMN', 'ACTION_NAME_HURRAH', 'ACTION_NAME_GREAT',
    'ACTION_NAME_EXCELLENT', 'ACTION_NAME_REFUSE', 'ACTION_NAME_COUP_FAILS',
    'ACTION_NAME_COUP_SUCCEEDS'
}

def load_csv_keys(csv_dir):
    csv_keys = {}
    pattern = os.path.join(csv_dir, "*.csv")
    for path in glob.glob(pattern):
        fname = os.path.basename(path)
        with open(path, 'r', encoding='latin1', errors='replace') as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                if not line or line.startswith('#'):
                    continue
                k = line.split(';')[0].strip()
                if k:
                    csv_keys[k.upper()] = (k, fname)
    return csv_keys

def parse_event_file(filepath, csv_keys):
    with open(filepath, 'r', encoding='latin1') as f:
        text = f.read()

    lines = text.splitlines(keepends=True)
    events = []
    
    # Parse event blocks
    pos = 0
    while True:
        m = re.search(r'\bevent\s*=\s*\{', text[pos:], re.IGNORECASE)
        if not m:
            break
        start_idx = pos + m.start()
        i = pos + m.end()
        depth = 1
        while i < len(text) and depth > 0:
            if text[i] == '{':
                depth += 1
            elif text[i] == '}':
                depth -= 1
            elif text[i] == '#':
                nl = text.find('\n', i)
                if nl == -1:
                    i = len(text)
                    break
                i = nl
            i += 1
        end_idx = i
        ev_text = text[start_idx:end_idx]
        
        id_m = re.search(r'\bid\s*=\s*(\d+)', ev_text)
        eid = int(id_m.group(1)) if id_m else None
        line_no = text.count('\n', 0, start_idx) + 1
        
        events.append({
            'id': eid,
            'line': line_no,
            'text': ev_text,
            'start': start_idx,
            'end': end_idx
        })
        pos = end_idx

    literals = []

    for ev in events:
        eid = ev['id']
        ev_lines = ev['text'].splitlines()
        in_act = False
        act_idx = 0
        
        for l_idx, el in enumerate(ev_lines):
            clean_l = el.split('#')[0].strip()
            if not clean_l:
                continue
            if re.search(r'\baction\s*=\s*\{', clean_l):
                in_act = True
                act_idx += 1
            
            # Check name
            nm = re.match(r'^\s*name\s*=\s*(.*)$', clean_l)
            if nm:
                val = nm.group(1).strip()
                is_quoted = val.startswith('"') and val.endswith('"') and len(val) >= 2
                raw = val[1:-1] if is_quoted else val
                raw = raw.strip()
                
                if raw.upper() in STANDARD_ENGINE_KEYS:
                    continue
                if raw.upper() not in csv_keys or (is_quoted and ' ' in raw):
                    act_letter = chr(ord('A') + act_idx - 1) if in_act else None
                    prop_type = f"action_{act_letter.lower()}" if in_act else "name"
                    suggested_key = f"EVT_{eid}_ACT{act_letter}" if in_act else f"EVT_{eid}_NAME"
                    literals.append({
                        'event_id': eid,
                        'line': ev['line'] + l_idx,
                        'type': prop_type,
                        'suggested_key': suggested_key,
                        'raw_value': raw,
                        'is_quoted': is_quoted,
                        'original_line': el
                    })

            # Check desc
            dm = re.match(r'^\s*desc\s*=\s*(.*)$', clean_l)
            if dm:
                val = dm.group(1).strip()
                is_quoted = val.startswith('"') and val.endswith('"') and len(val) >= 2
                raw = val[1:-1] if is_quoted else val
                raw = raw.strip()
                
                if raw.upper() in STANDARD_ENGINE_KEYS:
                    continue
                if raw.upper() not in csv_keys or (is_quoted and ' ' in raw):
                    suggested_key = f"EVT_{eid}_DESC"
                    literals.append({
                        'event_id': eid,
                        'line': ev['line'] + l_idx,
                        'type': 'desc',
                        'suggested_key': suggested_key,
                        'raw_value': raw,
                        'is_quoted': is_quoted,
                        'original_line': el
                    })

    return literals

def main():
    parser = argparse.ArgumentParser(description="Find string literals in Darkest Hour event files.")
    parser.add_argument("event_file", help="Path to event file (e.g. db/events/NewOrderAllied.txt)")
    parser.add_argument("--csv-dir", default="config", help="Path to config directory containing CSVs (default: config)")
    parser.add_argument("--json", action="store_true", help="Output results as JSON")
    args = parser.parse_args()

    if not os.path.exists(args.event_file):
        print(f"Error: Event file not found: {args.event_file}", file=sys.stderr)
        sys.exit(1)

    csv_keys = load_csv_keys(args.csv_dir)
    literals = parse_event_file(args.event_file, csv_keys)

    if args.json:
        print(json.dumps(literals, indent=2))
        return

    if not literals:
        print(f"No string literals or missing keys found in {args.event_file}. All strings properly localized!")
        return

    print(f"Found {len(literals)} string literals/unlocalized keys in {args.event_file}:\n")
    print(f"{'Line':<6} | {'Event ID':<10} | {'Type':<10} | {'Suggested Key':<20} | {'String Preview'}")
    print("-" * 85)
    for lit in literals:
        preview = (lit['raw_value'][:35] + '...') if len(lit['raw_value']) > 35 else lit['raw_value']
        print(f"{lit['line']:<6} | {str(lit['event_id']):<10} | {lit['type']:<10} | {lit['suggested_key']:<20} | {preview}")

if __name__ == '__main__':
    main()
