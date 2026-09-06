# GitHub Copilot Instructions

Beware that the context may be compacted without warning, therefore you MUST
periodically preserve important state in the `/memories` folder.

Do this especially when:
- the conversation has become substantially longer than the task itself;
- you have completed a major investigation;
- you have discovered important facts that would be expensive to rediscover;
- you have accumulated large amounts of debugging information;
- you are about to begin a substantially different phase of the task;
- you suspect context compaction may occur soon.

In addition, for long-running tasks, you should:
* Plan the work before executing it.
* Break large tasks into small, independently verifiable units.
* For tasks involving many similar items, test the procedure on one or a few items before processing the entire set.
* Keep a log of what has been done, and what remains to be done in persistent state files.
* Read the state files before executing next steps, to avoid duplicating work or losing track of progress.

## Verification

Before declaring a large task complete, verify that all requested items were processed and that the resulting files are actually correct.
