# Blueprint Attributes - Content Examples project

Plugin adding full BP support for GAS Attribute Sets.

https://blueprintattributes.github.io

`GBA_` is a prefix for Gameplay Blueprint Attributes, and used as a naming convention to prefix BP AttributeSets asset names across the project.

## Engine compatibility

Developed on 5.1 - Should be compatible with Unreal 5.1 versions and higher (you can tweak .uproject `EngineAssociation` field to match your launcher installed engine)

## Releases

Last packaged game build can be found in the releases page: https://github.com/BlueprintAttributes/GBA_ContentExamples/releases

## Modules

- BlueprintAttributes (Runtime) - Main runtime module
- BlueprintAttributesEditor (Editor) - Main editor module
- BlueprintAttributesDeveloper (UncookedOnly) - Uncooked only implementing custom K2 Nodes
- BlueprintAttributesScaffold (Editor) - Editor module for C++ generation / scaffolding (Attribute Wizard)
- BlueprintAttributesEditorCommon (Editor) - Editor module with shared common code and utilities

## Related

Related repositories:

- [BlueprintAttributesTest](https://github.com/BlueprintAttributes/BlueprintAttributesTests) - Unit / functional tests for the plugin
- [BlueprintAttributesDocumentation](https://github.com/BlueprintAttributes/BlueprintAttributesDocumentation) - Website and documentation for https://blueprintattributes.github.io