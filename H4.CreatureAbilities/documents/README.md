How to edit
---

In your */Plugins/* folder, you will find the file **CreatureAbilities.json**.

It is set up as an array of creatures with a list of the abilities they should be given.

**HOW TO USE**

* Do not remove creature objects!
  * If a creature is missing, the plugin will not activate.
  * Instead, remove the abilities you do not wish to be granted to any given creature.
* Do not modify creature names!
  * JSON format is case-sensitive.
  * It is easier to simply modify creature abilities.
* Do not remove Ability Lists!
  * Instead, remove unwanted abilities.
* Abilities may be added or removed by using any of the entries in **List of Creature Abilities.txt**
  * Abilities are not case-sensitive, so if you prefer to have them ALL UPPERCASE, that's up to you.
  * You should be able to add as many, or as few abilities as you choose to.
  * There are currently no checks for duplicate abilities!
  * If an unrecognized ability is provided, the plugin will not activate (be mindful of typos).
* If any irregularities are spotted, you should get a message with some more details.

![JSON details](https://github.com/RoseKavalier/H4MS/blob/master/H4.CreatureAbilities/documents/CreatureAbilities.png)
