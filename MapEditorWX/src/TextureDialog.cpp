#include "TextureDialog.h"
#include "MapEditorWX.h"
#include "MapEditorMainFrame.h"

const int TEX_ICON_SIZE = 32;
const int INTERVAL_X = 10;
const int INTERVAL_Y = 10;
const int TEX_TOP = 10;
const int TEX_LEFT = 10;

enum{
	ID_COLLECTION,
	ID_CLUT,
    ID_TYPE,
};

BEGIN_EVENT_TABLE(TextureDialog, wxDialog)
    // begin wxGlade: TextureDialog::event_table
    EVT_CHOICE(wxID_ANY, TextureDialog::OnType)
    EVT_CHOICE(wxID_ANY, TextureDialog::OnCollection)
    EVT_CHOICE(ID_TYPE, TextureDialog::OnCLUT)
    // end wxGlade
END_EVENT_TABLE()
TextureDialog::TextureDialog()
{
}
TextureDialog::~TextureDialog()
{
}
bool TextureDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Texture"));

    label_75 = new wxStaticText(this, wxID_ANY, wxT("type"));
    choice_30 = new wxChoice(this, ID_TYPE);
    panel_13 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER|wxTAB_TRAVERSAL);
	wxStaticText* label_collection = new wxStaticText(this, wxID_ANY, wxT("Collection"));
	choice_collection = new wxChoice(this, ID_COLLECTION);
	wxStaticText* label_clut = new wxStaticText(this, wxID_ANY, wxT("CLUT"));
	choice_clut = new wxChoice(this, ID_CLUT);

    panel_13->SetMinSize(wxSize(480, 120));
    panel_13->SetScrollRate(10, 10);

    wxFlexGridSizer* grid_sizer_44 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_45 = new wxFlexGridSizer(1, 6, 0, 0);
    grid_sizer_45->Add(label_collection, 0, 0, 0);
    grid_sizer_45->Add(choice_collection, 0, 0, 0);
    grid_sizer_45->Add(label_clut, 0, 0, 0);
    grid_sizer_45->Add(choice_clut, 0, 0, 0);
    grid_sizer_45->Add(label_75, 0, 0, 0);
    grid_sizer_45->Add(choice_30, 0, 0, 0);
    grid_sizer_44->Add(grid_sizer_45, 1, wxEXPAND, 0);
    grid_sizer_44->Add(panel_13, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_44);
    grid_sizer_44->Fit(this);
    Layout();

    //TODO Shapesファイルが読み込まれていない場合は警告を出して閉じる
    if(wxGetApp().getShapesManager()->isLoadedShapesFile()){
        hpl::error::caution("Shapes file not loaded");
        Destroy();
        return false;
    }

    //Shapesデータからサイズを計算します
	std::map<int, std::map<int, std::map<int, wxImage> > >* tmap = &((MapEditorMainFrame*)GetParent())->textureMap;

	//コレクションチョイスのセットアップ
	std::map<int, std::map<int, std::map<int, wxImage> > >::iterator it;
	int counter = 0;
	int collection = 0;
	for(it = tmap->begin(); it != tmap->end(); it ++){
		if(counter == 0){
			collection = it->first;
		}
		choice_collection->Insert(counter, getString("%d", it->first));
		counter ++;
	}
	
	//タイプ
	//TODO 

	//セットアップ
	setupDialog(collection);
    return result;
}
void TextureDialog::OnType(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (TextureDialog::OnType) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
void TextureDialog::OnCollection(wxCommandEvent &event)
{
	int collection = event.GetSelection();
	//TODO
}
void TextureDialog::OnCLUT(wxCommandEvent &event)
{
	int clut = event.GetSelection();
	//TODO
}
void TextureDialog::setFloor(bool floor)
{
    this->isFloor_ = floor;
}
void TextureDialog::drawPanel(int collection, int clut, std::map<int, wxImage>* imgMap)
{
	wxPaintDC dc(panel_13);
	wxSize size = panel_13->GetSize();
	dc.SetPen(*wxWHITE_PEN);
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawRectangle(0,0,size.GetWidth(), size.GetHeight());

	//パレット表示
	const int MERGIN_X = 10;
	const int MERGIN_Y = 10;
	const int ITEM_W = 100;
	const int ITEM_H = ITEM_W;
	const int ITEM_INTERVAL_X = 10;
	const int ITEM_INTERVAL_Y = 10;
	const int PITCH = 10;
}
void TextureDialog::setupDialog(int collection)
{
	std::map<int, std::map<int, std::map<int, wxImage> > >* tmap = &((MapEditorMainFrame*)GetParent())->textureMap;
	//setup clut choice
	choice_clut->Clear();
	std::map<int, std::map<int, wxImage> >::iterator it1;
	int clutCounter = 0;
	for(it1 = tmap->begin(); it1 != tmap->end(); it1 ++){
		choice_clut->Insert(clutCounter, getString("%d", it1->second));
		clutCounter ++;
	}
	//TODO
	drawPanel(collection, clut, &tmap->get(collection)[clut]);
}
