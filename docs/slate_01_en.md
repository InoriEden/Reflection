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

