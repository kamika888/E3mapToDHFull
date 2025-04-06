Summary of some notable changes:

-A lot of things are imported from TRP, certain things will probably require permission from Nightwing if the mod is to be released publicly. In particular the goal is to get the combat mechanics, unit costs and speeds closer to the TRP model, but ideally without importing the entire TRP tech tree and custom units. I'm not completely opposed to making tech tree changes but if possible i'd like to keep it close to the original. Ultimately it's still supposed to be DH on E3 map, not TRP on E3 map, but with combat mechanics brought a little closer to the TRP model.

-Manual IC building is basically disabled. Economic growth will happen on its own and it can be influenced slightly, but for the most part it's out of the player's control. I am really not a huge fan of the "IC building" mechanic, I find it both historically unrealistic and tedious as a form of gameplay.

-Starting IC for all countries is normalized to a of Madison's 1936 GNP estimates, slightly scaled down to reduce variance (both for historical and gameplay reasons). Internal IC distribution is changed, there are much fewer provinces with no IC at all.

-Sliders are disabled/repurposed, partly for technical reasons and partly because in their existing form they added no real value to gameplay. Regarding the technical aspect - for whatever reason there are a whole number of things in the game which simply cannot be done through events/decisions, they can only be done through sliders and sometimes minister modifiers. For example, changing the consumer goods demand - there is no event command that can change this to my knowledge, but sliders can.

-Manual puppet release is disabled, you can only release puppets by events/decisions in special cases. This is mostly for technical reasons. Also not all puppets are the same now, some are some which are much more unstable than others. Regarding the technical aspect - in wartime specifically, manual puppet release can really screw up a lot of things. By far the biggest one is that it changes province ownership rather than control, making it impossible to reliably use triggers such as "lost_national", "lost_VP", etc. It would be great if it was possible to only allow manual puppet release in peacetime but disallow in wartime, but alas I don't think there is a way to make that happen.

-The philosophy behind the national/claim distribution is actually taken largely from the original E3 map, but I liked their approach to it, so i just took it to its logical conclusion. It is a very inherently contentious and somewhat arbitrary issue by nature, i'm open to suggestions but would like to keep the overall idea the same.

-Most event chains are redone. For example, Spanish Civil War events are basically redone from scratch. The outcome of the SCW is also now a lot more consequential than it is either in TRP or even in vanilla DH.



Some other items to keep in mind:

-Since many values are not yet finalized, instead of being distributed through the proper configuration files where they normally belong, they are all set in a crude way at the start of the game for every country through the "initialSetup" event. This will eventually be changed once I'm confident that the values are final or almost final. What couldn't be done through initialSetup is done through the HoS modifiers.

-Manual declarations of war and alliance changes are currently disabled. This is PROBABLY a temporary measure, until some kind of event chain is written which allows both player and AI to react appropriately to ahistorical developments. TRP is famous for having extensive event chains designed just for such occasions and even they aren't really complete and don't always work very well, so it's a lot of work making sure all the various corner cases are covered. Maybe ultimately I will think about implementing something similar but it's not top priority.

-Certain decisions are fairly experimental and ultimately i might have to give up on them. For example, currently Vichy and the Allies are in a state of "cold war" with each other where they are technically at war but also have a non-aggression pact. This has some interesting effects and allows for certain neat gameplay situations, but could also theoretically produce problems and glitches if not properly controlled. I haven't yet decided if i want to keep that in.
