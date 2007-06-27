#include "EditorPreferencesDialog.h"
#include "ColorCustomizeDialog.h"

#include "MapEditorWX.h"
enum{
    ID_DEFAULT,
    ID_COLOR,
    ID_GRID,
    ID_FLAG,
};

BEGIN_EVENT_TABLE(EditorPreferencesDialog, wxDialog)
    // begin wxGlade: EditorPreferences::event_table
    EVT_BUTTON(ID_DEFAULT, EditorPreferencesDialog::OnDefault)
    EVT_BUTTON(wxID_OK, EditorPreferencesDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, EditorPreferencesDialog::OnCancel)
    EVT_CHOICE(ID_COLOR, EditorPreferencesDialog::OnColor)
    EVT_CHOICE(ID_GRID, EditorPreferencesDialog::OnGrid)
    // end wxGlade
END_EVENT_TABLE();
EditorPreferencesDialog::EditorPreferencesDialog()
{
}
EditorPreferencesDialog::~EditorPreferencesDialog()
{
}
bool EditorPreferencesDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Editor Preferences"));
    label_19 = new wxStaticText(this, wxID_ANY, wxT("Grid size"));
    choice_9 = new wxChoice(this, ID_GRID);
    checkbox[0] = new wxCheckBox(this, ID_FLAG, wxT("Show grid"));
    checkbox[1] = new wxCheckBox(this, ID_FLAG, wxT("Fit to grid"));
    checkbox[2] = new wxCheckBox(this, ID_FLAG, wxT("Show monsters"));
    checkbox[3] = new wxCheckBox(this, ID_FLAG, wxT("Show items"));
    checkbox[4] = new wxCheckBox(this, ID_FLAG, wxT("Show scenery"));
    checkbox[5] = new wxCheckBox(this, ID_FLAG, wxT("Show players"));
    checkbox[6] = new wxCheckBox(this, ID_FLAG, wxT("Show goals"));
    checkbox[7] = new wxCheckBox(this, ID_FLAG, wxT("Show sounds"));
    checkbox[8] = new wxCheckBox(this, ID_FLAG, wxT("Show annotations"));
    checkbox[9] = new wxCheckBox(this, ID_FLAG, wxT("Visual mode-Crossfair"));
    label_20 = new wxStaticText(this, wxID_ANY, wxT("Color set"));
    choice_10 = new wxChoice(this, ID_COLOR);
    checkbox[10] = new wxCheckBox(this, ID_FLAG, wxT("Show polygons"));
    checkbox[11] = new wxCheckBox(this, ID_FLAG, wxT("Show lines"));
    button_15 = new wxButton(this, ID_DEFAULT, wxT("Set as default"));
    button_13 = new wxButton(this, wxID_OK, wxT("OK"));
    button_14 = new wxButton(this, wxID_CANCEL, wxT("Cancel"));

    wxFlexGridSizer* sizer_45 = new wxFlexGridSizer(3, 1, 0, 0);
    wxBoxSizer* sizer_48 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_47 = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* sizer_50 = new wxFlexGridSizer(3, 1, 0, 0);
    wxBoxSizer* sizer_51 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_49 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_46 = new wxBoxSizer(wxHORIZONTAL);
    sizer_46->Add(label_19, 0, 0, 0);
    sizer_46->Add(choice_9, 0, 0, 0);
    sizer_45->Add(sizer_46, 1, wxEXPAND, 0);
    for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
        sizer_49->Add(checkbox[i], 0, 0, 0);
    }
    sizer_47->Add(sizer_49, 1, wxEXPAND, 0);
    sizer_51->Add(label_20, 0, 0, 0);
    sizer_51->Add(choice_10, 0, 0, 0);
    sizer_50->Add(sizer_51, 1, wxEXPAND, 0);
    sizer_50->Add(button_15, 0, 0, 0);
    sizer_47->Add(sizer_50, 1, wxEXPAND, 0);
    sizer_45->Add(sizer_47, 1, wxEXPAND, 0);
    sizer_48->Add(button_13, 0, 0, 0);
    sizer_48->Add(button_14, 0, 0, 0);
    sizer_45->Add(sizer_48, 1, wxEXPAND, 0);
    SetSizer(sizer_45);
    sizer_45->Fit(this);
    Layout();

    //グリッドサイズ
    char gridSizeNames[][100] = {"2 WU", "1/1 WU", "1/2 WU", 
        "1/4 WU", "1/8 WU"};
    for(int i = 0; i < NUMBER_OF_GLID; i ++){
        this->choice_9->Insert(wxString(wxConvertMB2WX(gridSizeNames[i])), i);
    }

    char colorSets[][100] = {"Forge", "Marathon", "Customize..."};
    for(int i = 0; i < 3; i ++){
        this->choice_10->Insert(wxString(wxConvertMB2WX(colorSets[i])), i);
    }
    
    MapEditorOneSetting* setting = &wxGetApp().setting;
    setupDialog(setting);

    return result;
}

void EditorPreferencesDialog::setupDialog(MapEditorOneSetting* setting)
{
    //メインから持ってくる
    for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
        this->checkbox[i]->SetValue(setting->flags[i]);
    }
    //グリッド
    this->choice_9->SetSelection(setting->getGridSizeIndex());
    //色
    ColorSettings* col = setting->getColorSetting();
    int colType = MapEditorOneSetting::checkColorType(col);
    if(colType < 0){
        colType = 2;
    }
    this->choice_10->SetSelection(colType);
    //コピーしておく
    memcpy(&this->colorSetting, col, sizeof(ColorSettings));
}

void EditorPreferencesDialog::OnOk(wxCommandEvent& wv)
{
    MapEditorOneSetting* setting = &wxGetApp().setting;
    //設定を反映します <en> feedback settings
    for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
        setting->flags[i] = this->checkbox[i]->GetValue();
    }
    //グリッド番号 <en> grid index
    int index = this->choice_9->GetSelection();
    setting->setGridSizeIndex(index);

    //カラー設定 <en> color setting
    int colType = this->choice_10->GetSelection();
    if(colType < 2){
        setting->setColorSetting(colType);
    }else{
        setting->setColorSetting(&this->colorSetting);
    }
    SetReturnCode(wxID_OK);
    Destroy();
}
void EditorPreferencesDialog::OnCancel(wxCommandEvent &ev)
{
    SetReturnCode(wxID_CANCEL);
    Destroy();
}
void EditorPreferencesDialog::OnColor(wxCommandEvent &ev)
{
    int type = ev.GetSelection();
    if(type == COL_CUSTOM){
        //カラー選択ダイアログを開く
        ColorCustomizeDialog dlg;
        dlg.Create(this, wxID_ANY, this->colorSetting);
        if(dlg.ShowModal() == wxID_OK){
            //色設定反映
            ColorSettings color = dlg.getColor();
            //TODO
            int newColType = MapEditorOneSetting::checkColorType(&color);
            if(newColType < COL_CUSTOM){
                //タイプから設定
                MapEditorOneSetting::setColorSetting(newColType, &this->colorSetting);
            }else{
                memcpy(&this->colorSetting, &color, sizeof(ColorSettings));
                newColType = COL_CUSTOM;
            }
            this->choice_10->SetSelection(newColType);
        }
    }
}

void EditorPreferencesDialog::OnDefault(wxCommandEvent &event)
{
    //設定を元に戻します
    MapEditorOneSetting def = MapEditorOneSetting::getDefaultSetting();
    setupDialog(&def);
}
void EditorPreferencesDialog::OnGrid(wxCommandEvent &ev)
{

}