The last time we discussed InitAssetEditor(). This time, let's focus on studying this function in detail. 

First, create a custom class that inherits from FAssetEditorToolkit.
<img width="911" height="271" alt="image" src="https://github.com/user-attachments/assets/e53e02e2-751b-46fd-b13d-400c359717d3" />
The InitEditor function calls FAssetEditorToolkit::InitAssetEditor(). 

This InitEditor function within the custom class is invoked by OpenAssetEditor() from the IAssetTypeActions mentioned in the previous section.

Focusing only on the code relevant to our purpose (how a window is inserted and displayed on top is described in the "Tab" section)
an examination of the source code reveals that the entire content of the editor is essentially what the SDockTab displays.

<img width="992" height="215" alt="image" src="https://github.com/user-attachments/assets/31d790b3-1c6d-4ca2-af93-8e696f7f9c1b" />
**Initialize an SDockTab.**

<img width="1219" height="307" alt="image" src="https://github.com/user-attachments/assets/46fa5c2f-4bab-4a11-a68b-9e2a43fd6ee8" />
**Generate a tutorial SWidget.**

<img width="158" height="80" alt="image" src="https://github.com/user-attachments/assets/38536eea-a143-4778-baa5-a07ec4a1e531" />

That's exactly what the image above shows, so the meaning of SetRightContent should be clear now. 
The same logic applies to methods like SetBackgroundContent and similar ones.

<img width="1386" height="65" alt="image" src="https://github.com/user-attachments/assets/72d17036-0721-42bc-ab03-8e395bad7716" />
The blurred background behind is the BackgroundContent.
Next comes the key part: the primary content displayed within the SDockTab.

<img width="1119" height="212" alt="image" src="https://github.com/user-attachments/assets/899c8bb8-000a-406d-8da2-bc694aeb1aed" />
Treat the SStandaloneAssetEditorToolkitHost class as an SWidget for now—similar to the previous cases
it's just a matter of assigning display content to it at a different location. 
Therefore, assigning content to the SStandaloneAssetEditorToolkitHost class determines the main content we will see.
<img width="720" height="257" alt="image" src="https://github.com/user-attachments/assets/a7aa3502-9f3a-4719-a4ca-84b47a9978b0" />
Further down, don't be overwhelmed by the numerous FUICommandLists—they are used to bind FUICommandInfo with FUIAction, 
which is necessary for initializing the menu bar and toolbar (though many of these bindings may not actually be used).

**How to Start Constructing the Menu Bar**
Enter the SetupInitialContent function and directly delve into the core function GenerateWidget(). 
What is done beforehand will also be mentioned within the GenerateWidget function.
<img width="1148" height="234" alt="image" src="https://github.com/user-attachments/assets/91ac5d88-97e5-4200-8714-2ef7ab35592b" />
<img width="1324" height="395" alt="image" src="https://github.com/user-attachments/assets/17071308-efed-473a-b639-d12424d76d36" />
In GenerateMenu(), the function returns GenerateMenuFromHierarchy(CollectHierarchy(Name), InMenuContext).

Let's first understand CollectHierarchy(). 
The main purpose of this function is to gather both the registered UToolMenu and its parent class UToolMenu into an array and return it.
<img width="1060" height="320" alt="image" src="https://github.com/user-attachments/assets/e861564f-875b-4f5a-9813-929bbbe3331e" />
FindMenu is the function used to locate registered menus. 
It first searches for the UToolMenu that you registered yourself, which is done at the beginning of the SetupInitialContent function.

<img width="1168" height="238" alt="image" src="https://github.com/user-attachments/assets/9021698c-2cdd-4be4-9039-bf32d3041e75" />
Subsequently, the parent class name is passed to CurrentMenuName, then to AdjustedMenuName to search for the parent class's UToolMenu.
This process repeats until the parent class name is empty, at which point the loop exits.
Here, the parent class name is MainFrame.MainMenu, which was assigned as the parent class MainFrame during the registration step mentioned earlier.

<img width="1150" height="308" alt="image" src="https://github.com/user-attachments/assets/f7002ecb-79ef-4899-8771-6751c7499402" />

All registrations for the parent class are handled within MakeMainMenu.
<img width="1209" height="365" alt="image" src="https://github.com/user-attachments/assets/6cd3930e-9f28-48ef-acbd-a9a6e8284496" />
**RegisterMainMenu performs the registration.**

The next step is to combine the parent class's and your own UToolMenu within AssembleMenuHierarchy.
<img width="964" height="208" alt="image" src="https://github.com/user-attachments/assets/c33a1d66-ae53-4373-9ed9-2576cc695ad6" />
As can be seen, the parent class has four sections (File, Edit, Window, Help), while your own has (File, Help).
There is also an Asset section, but it hasn't been registered. The CreateDefaultStandaloneMenuBar function within the SetupInitialContent function adds these, 
and the registration for your own (File, Help) sections is also handled in this function.

<img width="1304" height="296" alt="image" src="https://github.com/user-attachments/assets/deabfc42-d942-4ef0-b869-2519ce6578ef" />
Afterward, within the AssembleMenuHierarchy function of GenerateMenuFromHierarchy, the task is to integrate the sections from both UToolMenus.

<img width="1151" height="338" alt="image" src="https://github.com/user-attachments/assets/06c88349-0cd9-4a77-aa29-a7b70a956506" />
After that, we arrive at the GenerateWidget function. Once you understand how the parameter UToolMenu* GeneratedMenu is obtained, 
there isn’t much left to explain—since the focus is on generating the menu bar, let’s proceed directly to this step for translation.

<img width="1286" height="205" alt="image" src="https://github.com/user-attachments/assets/3b6b6b4a-72ed-4203-9d9c-9d31c45f7bdf" />
Inside the PopulateMenuBarBuilder function, each Block from the integrated sections will be inserted one by one into the FMenuBarBuilder.
If any extenders are added, the delegates bound to those extenders will be invoked within the ApplyHook() function.

**How to Construct the Toolbar**
Similar to the menu bar...
<img width="1029" height="171" alt="image" src="https://github.com/user-attachments/assets/5ce656b2-942d-43a0-9bfb-beca48aba289" />
There's not much code, so I won't elaborate further.

The next section describes how to add the editor to the viewport.

Reference:
《调教UE5：编辑器拓展指南》Tab 探索 https://zhuanlan.zhihu.com/p/628655599





