# GitHub Copilot Instructions

## Long-running tasks

For large tasks involving many files, items, or external resources:

* Plan the work before executing it.
* Break large tasks into small, independently verifiable units.
* For tasks involving many similar items, test the procedure on one or a few items before processing the entire set.
* Maintain persistent progress files for sufficiently large tasks so work can be resumed after interruption.
* Update the progress file after completing meaningful batches.
* Verify completed work rather than relying on conversational memory.

## Tool use

* Prefer simple, reliable commands over complicated shell one-liners.
* If a command fails, diagnose the cause before retrying it; do not repeatedly run the same failing command.
* For large operations, prefer scripts that can be inspected and corrected over fragile shell commands.
* Do not issue large numbers of concurrent network requests. Respect rate limits and use modest/sequential batches.
* When a transient network operation fails, retry with appropriate delay rather than immediately increasing concurrency.

## Error recovery

When an approach repeatedly fails, stop and reconsider the approach rather than entering a retry loop.

For long tasks, a failure affecting one item should not unnecessarily prevent independent items from being processed.

## Context management

* Avoid unnecessarily dumping large files, command outputs, or search results into the conversation.
* Store useful intermediate state in files when it needs to persist.
* Before resuming a long task, inspect the actual workspace and any progress state rather than relying solely on conversation history.

## Completion

Before declaring a large task complete, verify that all requested items were processed and that the resulting files are actually correct.
