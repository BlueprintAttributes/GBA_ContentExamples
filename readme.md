# Blueprint Attributes - Content Examples project

Plugin adding full BP support for GAS Attribute Sets.

https://blueprintattributes.github.io

`GBA_` is a prefix for Gameplay Blueprint Attributes, and used as a naming convention to prefix BP AttributeSets asset names across the project.

## Engine compatibility

Developed on 5.1 - Should be compatible with Unreal 5.1 versions and higher (you can tweak .uproject `EngineAssociation` field to match your launcher installed engine)

## Releases

Last packaged game build can be found in the releases page: https://github.com/BlueprintAttributes/GBA_ContentExamples/releases

## Maps

In `/Game/Maps`

- `01_BlueprintAttributes_Welcome` - Default entry level map
- `02_Builtin_Clamping` - Built-in clamping example
- `03_MMC` - Modifier Magnitude Calculation example - Fatigue / Weight attributes with MoveSpeed / JumpHeight derived attributes (Warning: MoveSpeed specifically is not properly implemented for multiplayer, proper MoveSpeed replication on CMC goes a bit beyond the scope of this demo project)
- `04_ExecClasses` - Gameplay Effect Execution Class example - Damage output calculation based on AttackPower and Armor mitigation.
- `05_SaveGame` - Save Game example - Gold attribute acting as a currency that gets increased when a box is destroyed. Ctrl+S to save the value, Ctrl+L to load it back.

In a packaged build, you can navigate to a given map using the console command `open Map_Name`, for instance `open 05_SaveGame`.

## Related

Related repositories:

- [BlueprintAttributesTest](https://github.com/BlueprintAttributes/BlueprintAttributesTests) - Unit / functional tests for the plugin
- [BlueprintAttributesDocumentation](https://github.com/BlueprintAttributes/BlueprintAttributesDocumentation) - Website and documentation for https://blueprintattributes.github.io