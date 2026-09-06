# Agent Instructions

## Context Management

Keep the active context focused on information needed for the current task. Conversation context may be compacted, so preserve important state in persistent memory.

### Large files

**Do not read large files in their entirety by default.**

When working with a large file (50KB or greater):

* Search for relevant sections, symbols, records, or ranges first.
* Read and modify the file in logical chunks rather than loading the entire file into context.
* Avoid re-reading the entire file merely to verify a localized change; verify the affected portions instead.
* Prefer incremental edits and targeted tests over rewriting the entire file with a script.
* If the task naturally divides into independent sections, process them independently and use subagents when practical.
* Only load the entire file when its complete contents are genuinely required to reason about the task.

### Persistent memory

Use the `memory` tool extensively to preserve important task state.

Update persistent memory after major discoveries, decisions, completed phases, failed approaches, or whenever information would otherwise need to be reconstructed after context compaction.

Keep memory concise: record conclusions, current state, relevant files, tests, and next steps—not conversation transcripts or large code blocks.

Before starting work, inspect relevant existing memory. After compaction, use persistent memory to reconstruct the task state before proceeding.
