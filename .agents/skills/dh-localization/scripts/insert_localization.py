#!/usr/bin/env python3
"""
Automatically migrate string literals from event files into config/modtext.csv.
Usage:
    python insert_localization.py <event_file_path> [--modtext config/modtext.csv] [--apply]
"""
import os, sys, re, argparse
from extract_strings import load_csv_keys, parse_event_file

def format_csv_row(key, text):
    # Escape internal quotes if necessary
    return f"{key};{text};{text};{text};{text};{text};{text};{text};{text};;;X\r\n"

def find_insertion_index(modtext_lines, event_filename, event_id):
    # 1. Look for section matching event_filename (e.g. #NewOrderAllied.txt;;;;;;;;;;;X)
    section_name = f"#{os.path.basename(event_filename)}"
    section_start = None
    section_end = len(modtext_lines)
    
    for i, line in enumerate(modtext_lines):
        if line.startswith(section_name):
            section_start = i
            break
            
    if section_start is not None:
        for i in range(section_start + 1, len(modtext_lines)):
            if modtext_lines[i].startswith('#'):
                section_end = i
                break
                
        # Find best numerical insertion spot within section
        best_pos = section_end
        for i in range(section_start + 1, section_end):
            m = re.search(r'EVT_(\d+)_', modtext_lines[i])
            if m:
                curr_id = int(m.group(1))
                if curr_id > event_id:
                    return i
                elif curr_id == event_id:
                    best_pos = i + 1
        return best_pos

    # 2. Fallback: Find closest numeric ID across all entries
    best_pos = None
    for i, line in enumerate(modtext_lines):
        m = re.search(r'EVT_(\d+)_', line)
        if m:
            curr_id = int(m.group(1))
            if curr_id <= event_id:
                best_pos = i + 1
                
    return best_pos if best_pos is not None else len(modtext_lines) - 1

def apply_localization(event_file, modtext_path, apply=False):
    csv_dir = os.path.dirname(modtext_path) or "config"
    csv_keys = load_csv_keys(csv_dir)
    literals = parse_event_file(event_file, csv_keys)

    if not literals:
        print(f"No string literals found in {event_file}. Nothing to do.")
        return

    print(f"Discovered {len(literals)} string literals to migrate.")

    with open(modtext_path, 'rb') as f:
        modtext_raw = f.read()

    modtext_str = modtext_raw.decode('latin1')
    modtext_lines = modtext_str.splitlines(keepends=True)

    with open(event_file, 'rb') as f:
        event_raw = f.read()
    event_str = event_raw.decode('latin1')

    # Sort literals by line descending for in-place text replacement
    literals_by_line_desc = sorted(literals, key=lambda x: x['line'], reverse=True)

    # Group new CSV rows by insertion index
    insertions = [] # (index, row_str, key, event_id)
    
    for lit in literals:
        row_str = format_csv_row(lit['suggested_key'], lit['raw_value'])
        ins_idx = find_insertion_index(modtext_lines, event_file, lit['event_id'])
        insertions.append((ins_idx, row_str, lit['suggested_key'], lit['event_id']))

    # Sort insertions by index descending so insertion doesn't mess up subsequent indices
    insertions.sort(key=lambda x: (x[0], x[3]), reverse=True)

    new_modtext_lines = list(modtext_lines)
    for ins_idx, row_str, key, eid in insertions:
        new_modtext_lines.insert(ins_idx, row_str)

    new_modtext_str = "".join(new_modtext_lines)

    # Replace literals in event_str
    new_event_str = event_str
    for lit in literals_by_line_desc:
        raw_val = lit['raw_value']
        key = lit['suggested_key']
        # Find exact line
        orig_line = lit['original_line']
        if lit['is_quoted']:
            replaced_line = re.sub(r'=\s*"' + re.escape(raw_val) + r'"', f'= {key}', orig_line)
        else:
            replaced_line = re.sub(r'=\s*' + re.escape(raw_val), f'= {key}', orig_line)
        new_event_str = new_event_str.replace(orig_line, replaced_line, 1)

    print(f"\nPlan Summary:")
    print(f"  - {len(literals)} new rows to insert into {modtext_path}")
    print(f"  - {len(literals)} string literal occurrences to replace in {event_file}")

    if not apply:
        print("\n[DRY RUN] No files were modified. Run with --apply to execute changes.")
        for lit in literals:
            print(f"  + {lit['suggested_key']}: \"{lit['raw_value'][:50]}...\"")
        return

    # Write files
    assert new_modtext_str.endswith("#EOF;;;;;;;;;;;X\r\n") or new_modtext_str.endswith("#EOF;;;;;;;;;;;X\n"), "modtext must end with #EOF"

    with open(modtext_path, 'wb') as f:
        f.write(new_modtext_str.encode('latin1'))

    with open(event_file, 'wb') as f:
        f.write(new_event_str.encode('latin1'))

    print(f"\n[SUCCESS] Updated {modtext_path} and {event_file} successfully!")

def main():
    parser = argparse.ArgumentParser(description="Migrate string literals to modtext.csv.")
    parser.add_argument("event_file", help="Path to event file (e.g. db/events/NewOrderAllied.txt)")
    parser.add_argument("--modtext", default="config/modtext.csv", help="Path to modtext.csv (default: config/modtext.csv)")
    parser.add_argument("--apply", action="store_true", help="Apply changes directly to files")
    args = parser.parse_args()

    if not os.path.exists(args.event_file):
        print(f"Error: Event file not found: {args.event_file}", file=sys.stderr)
        sys.exit(1)
    if not os.path.exists(args.modtext):
        print(f"Error: modtext file not found: {args.modtext}", file=sys.stderr)
        sys.exit(1)

    apply_localization(args.event_file, args.modtext, apply=args.apply)

if __name__ == '__main__':
    main()
