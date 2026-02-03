UE Slate Learning Notes 1 - Opening a Custom Editor 1
<img width="1679" height="357" alt="image" src="https://github.com/user-attachments/assets/5b28fd1d-ba7f-4729-aa7e-399720cec7b1" />
While reviewing BlueprintEditorModule, I found that there are two ways to open the Blueprint Editor according to the comments.

In this article, I chose to use
GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset
to open the editor.

The core logic of OpenEditorForAsset is implemented by invoking
OpenAssetEditor through IAssetTypeActions.
