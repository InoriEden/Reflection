UE Slate Learning Notes 1 - Opening a Custom Editor 1
<img width="1679" height="357" alt="image" src="https://github.com/user-attachments/assets/5b28fd1d-ba7f-4729-aa7e-399720cec7b1" />
While reviewing BlueprintEditorModule, I found that there are two ways to open the Blueprint Editor according to the comments.

In this article, I chose to use
GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset
to open the editor.

The core logic of OpenEditorForAsset is implemented by invoking
OpenAssetEditor through IAssetTypeActions.
<img width="978" height="51" alt="image" src="https://github.com/user-attachments/assets/ef106b61-0eb3-4f2c-b747-fd67a1ba664d" />
<img width="1042" height="56" alt="image" src="https://github.com/user-attachments/assets/35859136-cb08-4a2a-9022-6e9c7984f568" />
<img width="1485" height="405" alt="image" src="https://github.com/user-attachments/assets/d6defd6b-0f06-45cd-b532-d486339a9e25" />
In the function GetAssetTypeActionsForClass, the IAssetTypeActions is obtained by traversing the AssetTypeActionsList array. Since the blueprint already has a default IAssetTypeActions for blueprints, to open a custom editor, a new IAssetTypeActions needs to be created, and its Supported class should be set to UBlueprint.
<img width="1324" height="231" alt="image" src="https://github.com/user-attachments/assets/dcda210a-7573-4d01-b6e3-5631db4a3b8b" />
_________________________________________________**Custom IAssetTypeActions Header File**_____________________________________________
<img width="1415" height="433" alt="image" src="https://github.com/user-attachments/assets/eeb3d719-6a17-44a7-9f72-9ffffc602902" />
After creation, it is also necessary to add your custom IAssetTypeActions to the AssetTypeActionsList array in the FAssetToolsModule to ensure it is properly registered and accessible.
<img width="886" height="100" alt="image" src="https://github.com/user-attachments/assets/5ab8e654-3334-445b-9b6d-56d0f290ce2e" />
After that, call OpenEditorForAsset().
<img width="976" height="63" alt="image" src="https://github.com/user-attachments/assets/87b28363-875b-4c18-a299-457354f6b86c" />
Finally, the crucial step is to create the custom editor. This requires defining a class that inherits from FAssetEditorToolkit, utilizing its InitAssetEditor method to generate a custom editor interface. The original blueprint IAssetTypeActions follows this same pattern.

Within InitAssetEditor, the framework for constructing the editor is defined. This includes how the menu bar and toolbars are generated, how individual items are created and inserted into their appropriate positions, and also allows for extensive customization and modification of this custom editor.




