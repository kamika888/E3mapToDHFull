# GitHub Copilot Instructions

Beware that the context may be compacted without warning, therefore you must
periodically preserve important state in `memory/current-task.md` and other files in the `memory` directory.

Do this especially when:
- the conversation has become substantially longer than the task itself;
- you have completed a major investigation;
- you have discovered important facts that would be expensive to rediscover;
- you have accumulated large amounts of debugging information;
- you are about to begin a substantially different phase of the task;
- you suspect context compaction may occur soon.

Before compaction becomes necessary, ensure that `memory/current-task.md`
contains enough information for another agent instance to continue the work
without reconstructing the entire conversation.

In addition, for long-running tasks, you should:
* Plan the work before executing it.
* Break large tasks into small, independently verifiable units.
* For tasks involving many similar items, test the procedure on one or a few items before processing the entire set.

## Verification

Before declaring a large task complete, verify that all requested items were processed and that the resulting files are actually correct.
