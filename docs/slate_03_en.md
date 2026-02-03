https://zhuanlan.zhihu.com/p/628655599
From the linked article, understand the following correspondences:
<img width="339" height="254" alt="image" src="https://github.com/user-attachments/assets/f49e4d9e-5a7a-4a0d-96fa-a95bad61876c" />
In the FAssetEditorToolkit::InitAssetEditor function, the custom editor is displayed in the viewport by calling FGlobalTabmanager::Get()->InsertNewDocumentTab. 
Before understanding this function, let’s first look at the simplest way to invoke and display a tab in the viewport: InvokeTab().

Inside InvokeTab, we enter the InvokeTab_Internal function. The comment for this function describes its purpose:
<img width="964" height="348" alt="image" src="https://github.com/user-attachments/assets/226ffcf2-1ee7-47ec-9d7a-96595ea2b4a0" />
**InvokeTab Process**
**1. Check if an instance already exists**
First, check whether RegisterTabSpawner has been called for registration. If it has been registered, verify if it has already been invoked.
For tabs that have been invoked before, the FTabSpawnerEntry within its TabManager stores the pointer (SpawnedTabPtr) to the opened tab.

<img width="1013" height="418" alt="image" src="https://github.com/user-attachments/assets/c2d20931-c7e7-440d-a976-aad3b3906fba" />
It can be observed that in the subsequent RestoreArea_Help(), SpawnTab() is called, and a value is assigned to SpawnedTabPtr. 
The value assigned here is precisely the return value of the delegate FOnSpawnTab that was registered when RegisterTabSpawner was invoked.

<img width="1237" height="449" alt="image" src="https://github.com/user-attachments/assets/0eb607a6-5edd-4f27-a272-9b926a9aeb26" />
**2. Search among the closed CollapsedDockAreas (FArea) to see if there is a Stack (SDockingTabStack) that matches the TabId.**
That is, if this Tab has been opened before but is now closed, CollapsedDockAreas will record the closed DockArea.

Within FindPotentiallyClosedTab, we enter FindTabInCollapsedAreas. Here, TabMatcher is passed in as a predicate—it overloads the () operator.
The main task of the FindTabInCollapsedAreas function is to traverse the Area, then the Area/Splitter, and finally iterate through its own Stack. The Stack stores an array of Tabs.

<img width="1239" height="464" alt="image" src="https://github.com/user-attachments/assets/db9bf660-0048-4e17-817e-94747634c2cc" />
The TArray calls IndexOfByPredicate to determine whether the tab belongs to this array. 
If it returns INDEX_NONE, it indicates that the tab does not exist in this stack.
Here, IndexOfByPredicate is passed a predicate as its argument.

<img width="992" height="254" alt="image" src="https://github.com/user-attachments/assets/61dd93ab-f2ed-4349-82f4-59cf46d4e799" />
SizeType refers to InAllocator::SizeType.

<img width="1440" height="420" alt="image" src="https://github.com/user-attachments/assets/5f3299bc-65c7-41e1-82de-a801f028af3a" />

<img width="700" height="386" alt="image" src="https://github.com/user-attachments/assets/39c67596-e7f3-4cb3-b5e0-b2803890fb4d" />
Therefore, SizeType is essentially an int32, which returns the position (index) within the TArray. ElementType is FTab. Pred() calls the overloaded () operator of FTabMatch; 
when a match is found, the addresses are subtracted to return an offset, thereby determining the position (index) within the TArray.

If the tab is not found in the closed Area, the search continues in the active Area.
If the corresponding tab is still not found in either, the process proceeds to the next step.

**3.Start within a new SWindow.**
The core logic is essentially contained within RestoreArea(), which mainly involves traversal and recursion. The incoming FLayoutNode is first used to obtain the Area.

If bDockNeedsNewWindow is true, a new window is created using SNew. Then, FSlateApplication::Get().
AddWindow is called to add the new window, and FSlateApplication::Get().AddWindow(NewWindow)->SetContent sets the content of the SDockingArea. 
SArea exists to assign values to SDockingArea, and RestoreSplitterContent is called to populate SDockingArea with content.

<img width="934" height="448" alt="image" src="https://github.com/user-attachments/assets/1ab6ef0a-a615-4240-8718-ce90cb5faabb" />
Within RestoreSplitterContent, SArea is traversed to obtain its child FLayoutNode. 
Here, FLayoutNode essentially refers to FStack, as seen in how FArea is initialized.

<img width="719" height="104" alt="image" src="https://github.com/user-attachments/assets/a4e6040f-9673-490d-82b8-8df9363fe7c2" />
**Relationship Diagram**
Here, it recursively calls the RestoreArea_Helper function again, this time entering its own branch as FStack.

<img width="1083" height="483" alt="image" src="https://github.com/user-attachments/assets/827257a8-78f2-490d-80a6-10a66e255a75" />
Many conditional checks are performed here, and since they are commented, no explanation is needed. The key focus is on the following section.

<img width="875" height="447" alt="image" src="https://github.com/user-attachments/assets/09dc23b2-0be8-4942-884f-d9a95c904d07" />

What is being traversed here is the Tabs array within the Stack. Referring back to the relationship diagram above, the SpawnTab function essentially performs the following steps:
First, it checks if an FTabSpawnerEntry with this name has been registered via RegisterTabSpawner.
If found, it then checks whether the CanSpawnTab delegate is bound—if so, it executes it. 
Next, it checks if the OnSpawnTab delegate is bound—if so, it executes it and returns a TSharedPtr<SDockTab>. 
After that, this SDockTab is assigned values, and the SpawnedTabPtr in the FTabSpawnerEntry is pointed to this SDockTab. 
This way, the next time it is opened, it can determine whether it is the same tab opened previously, which aligns with the check performed at the beginning of the Invoke call.

<img width="1092" height="434" alt="image" src="https://github.com/user-attachments/assets/456567ff-fba6-47f4-b48b-7875e7ea5296" />
Finally, the SDockingTabStack is assigned. When the SWidget is rendered through OnPaint() or Paint(), it starts from the FArea and progressively moves down to its children layer by layer.

**InsertNewDocumentTab**
Returning to the InsertNewDocumentTab function called when generating the editor, we directly enter the OpenUnmanagedTab function.
<img width="1033" height="398" alt="image" src="https://github.com/user-attachments/assets/0fbcda38-bf71-45c2-99a7-4f9176e31309" />
The passed Search is FLiveTabSearch, which looks for any already opened Tab. If one exists, it will be inserted directly rather than opened in a new window.

<img width="1032" height="202" alt="image" src="https://github.com/user-attachments/assets/461c64b3-cf13-41cf-8315-dc9b028061ce" />
This is done by comparing the LayoutIdentifier. At the start of calling InvokeTab's SpawnTab and InsertNewDocumentTab, each SDockTab is assigned a value.

<img width="1257" height="758" alt="image" src="https://github.com/user-attachments/assets/28ff9a02-fa1f-46e7-a110-40b2d75553f3" />
**This image does not depict the custom editor interface but was generated via InsertNewDocumentTab for testing convenience.**

For example, if the passed PlaceholderId is "uiui", a new Tab will be directly inserted beside it.

When OpenTab is called, it already locates the corresponding SDockingTabStack via the SDockTab, and then adds the new SDockTab to the Tabs array of that SDockingTabStack through OpenTab.

If the passed FName does not find an actively open LiveTab, and FindPotentiallyClosedTab also fails to locate a previously closed one, then InvokeTab is invoked to create a new window.

