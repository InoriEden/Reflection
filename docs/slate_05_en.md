I discovered that UMG Blueprints cannot dynamically generate UMG Animations, which often feels inconvenient. 
I decided to examine how the UMG editor generates animations via blueprints and animation buttons.
<img width="1440" height="714" alt="image" src="https://github.com/user-attachments/assets/454ccf03-40ac-448d-88b6-58686cdcb6f0" />

First, I used WidgetReflector to locate the source code and found that the code for the "Add Animation" button is written in AnimationTabSummoner.cpp at line 288.

**《调教UE5：编辑器拓展指南》Tab 探索**https://zhuanlan.zhihu.com/p/628655599
This expert's article analyzes the FWorkflowCentricApplication class, which inherits from FAssetEditorToolkit. It's important to understand this first, as FWorkflowCentricApplication is the parent class of the UMG Editor. Here's a brief summary:

**1**The key feature of FWorkflowCentricApplication is its support for multiple modes (FApplicationMode).
The SetCurrentMode function allows switching between these modes. Switching modes essentially changes the entire editor's page layout and elements.
Taking the UMG Editor (FWidgetBlueprintEditor) as an example, you can see it has two modes.
<img width="1170" height="352" alt="image" src="https://github.com/user-attachments/assets/703b429e-3f68-4a7e-88aa-db5fc70addc5" />
**2**Upon entering the initial FWidgetDesignerApplicationMode mode, you can see that its constructor generates its own page layout. Most importantly, TabFactories.RegisterFactory

<img width="1440" height="170" alt="image" src="https://github.com/user-attachments/assets/cbd6910e-fe09-4495-af57-36cdbaab9126" />
TabFactories is an instance of the FWorkflowAllowedTabSet class, which internally contains a TMap (a UE container) storing FWorkflowTabFactory objects. 
The RegisterFactory function is used to add tab factory instances into this map.
<img width="1440" height="83" alt="image" src="https://github.com/user-attachments/assets/11c0db48-71d1-4136-9fd2-f5471bd14894" />

**3**The FWorkflowTabFactory is actually the parent class of the AnimationTabSummoner class we just discovered using the Widget Reflector. 
Therefore, FWorkflowTabFactory essentially stores the UI elements that make up the page layout. The overall workflow is as follows:
<img width="1440" height="283" alt="image" src="https://github.com/user-attachments/assets/f576d6f8-0311-414e-b27d-1b977a0d1830" />

**4**In the PushTabFactories function, the code iterates through the Factories stored in the FWorkflowAllowedTabSet. For each iterated FWorkflowTabFactory, it calls the RegisterTabSpawner function to register it. 
The key step is FWorkflowTabFactory::OnSpawnTab -> SpawnTab() -> CreateTabBody().

Therefore, we can see that CreateTabBody, which must be overridden by derived classes of FWorkflowTabFactory, is invoked here. 
The return value of CreateTabBody is the actual content we see in the interface. In the case of AnimationTabSummoner, it returns an SUMGAnimationList.
<img width="778" height="158" alt="image" src="https://github.com/user-attachments/assets/04f4b332-183f-41fc-bdfc-6c91ba7959c1" />

And the SUMGAnimationList is the actual Tab (the content panel/window) displayed in that slot.
<img width="286" height="327" alt="image" src="https://github.com/user-attachments/assets/b8180b8d-16bc-4ed3-b284-585511259906" />

Now that we have a clear understanding of the structure, let's examine what happens after clicking the "+ Animation" button to understand how to dynamically generate a UMG Animation button.
<img width="482" height="145" alt="image" src="https://github.com/user-attachments/assets/81e8336e-a663-4e1e-bd96-a921907dacac" />

The core logic is implemented in the OnNewAnimationClicked function. Of course, this creates an empty animation. 
For details about animation-related components like Tracks, MovieScene, and Channels, you can refer to the explanations from this expert (the original author mentioned in your query).
**reference**
https://zhuanlan.zhihu.com/p/364150799



