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

