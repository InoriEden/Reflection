This section covers displaying custom content. In UE, UI elements are generally displayed in the editor interface through SWidget. 
Creating an SWidget is typically done using the SNew or SAssignNew macros. Let’s first examine these two macros.

In FAssetEditorToolkit::InitAssetEditor, you can see:
<img width="780" height="113" alt="image" src="https://github.com/user-attachments/assets/1db24bc4-5a81-43ca-9335-afdc504c6a2e" />
The first parameter is the variable to be assigned. The second parameter is the class of that variable, and the next two parameters are filled according to the constructor (Construct) of that class. SStandaloneAssetEditorToolkitHost::Construct corresponds to this, so fill in FTabManager and FName.

<img width="802" height="40" alt="image" src="https://github.com/user-attachments/assets/0e8b59f1-c872-410e-bce0-7caf68d4fe6f" />
**SStandaloneAssetEditorToolkitHost::Construct**

Why are parameters filled based on the Construct function? Because of the overloaded <<= operator. When using SNew or SAssignNew, <<= is used to conveniently assign values to WidgetType::FArguments() via ., as shown in the example above with .OnRequestClose. Within the <<= operator, the Construct method of that class is also called to perform the assignment.
<img width="801" height="367" alt="image" src="https://github.com/user-attachments/assets/3df37de6-47e9-46cd-a8cc-319ce1450f6d" />

Next, we will customize an SWidget, which can inherit from one of the three categories: SCompoundWidget, SPanel, or SLeafWidget. Here, we will reference the implementation of the engine's SButton and modify it to create our own.

The macros SLATE_BEGIN_ARGS() and SLATE_END_ARGS() are mandatory. Between these two macros, variables and delegates are declared for the custom widget using SLATE_ARGUMENT, SLATE_ATTRIBUTE, and SLATE_EVENT. Since it inherits from SCompoundWidget, it includes slots for child widgets, so a SLATE_DEFAULT_SLOT must be declared to host child SWidget instances.
<img width="701" height="412" alt="image" src="https://github.com/user-attachments/assets/beaf816a-d95b-4fd9-938a-625e764da56e" />

In the Construct function, not only are the variables of the class assigned values, 
but if there are slots, the contents within the slots are also passed to the parent class. 
This facilitates retrieval and rendering in the OnPaint() function.
<img width="792" height="442" alt="image" src="https://github.com/user-attachments/assets/31e88e1c-9a94-4156-ae66-9a65dee865e0" />
The [] operator is overloaded for SBorder. 
In the Construct function of SBorder, the slot content is similarly passed to the parent class and ultimately stored in the ChildSlot of SCompoundWidget.
<img width="249" height="129" alt="image" src="https://github.com/user-attachments/assets/6ab963f9-a078-4336-ac84-0e879c533119" />

When SButton begins rendering, FSlateDrawElement::MakeBox draws a Button, and then SCompoundWidget::OnPaint is called to render the child elements within SButton.
<img width="1265" height="397" alt="image" src="https://github.com/user-attachments/assets/43d7e56f-aa2a-4ce5-8250-3b9cdf8e197f" />
The previously mentioned SCompoundWidget::ChildSlot will be utilized in ArrangeChildren.

**reference**
https://zhuanlan.zhihu.com/p/543267900?utm_id=0
