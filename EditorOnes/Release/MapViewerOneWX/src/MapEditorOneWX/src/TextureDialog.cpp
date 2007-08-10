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
    ID_SCROLL,
};

static void drawPanel(int collection, int clut, std::map<int, wxImage>* imgMap,
                              wxDC* dc, TextureArea* panel)
{
//	wxWindowDC dc(panel_13);
    wxSize size = panel->GetMaxSize();
	dc->SetPen(*wxWHITE_PEN);
	dc->SetBrush(*wxWHITE_BRUSH);
	dc->DrawRectangle(0,0,size.GetWidth(), size.GetHeight());

	//パレット表示
	const int MERGIN_X = 10;
	const int MERGIN_Y = 10;
	const int ITEM_W = 40;
	const int ITEM_H = ITEM_W;
	const int ITEM_INTERVAL_X = 10;
	const int ITEM_INTERVAL_Y = 10;
    const int PITCH = (size.GetWidth() - MERGIN_X * 2) / (ITEM_W + ITEM_INTERVAL_X);
    
	if(wxGetApp().getShapesManager()->isLoadedShapesFile()){

		std::map<int, wxImage>::iterator it;
		int counter = 0;
		double rad = hpl::math::getRadianFromDegree(90);
		for(it = imgMap->begin(); it != imgMap->end(); it ++){
			int x = (counter % PITCH) * (ITEM_W + ITEM_INTERVAL_X) + MERGIN_X;
			int y = (counter / PITCH) * (ITEM_H + ITEM_INTERVAL_Y) + MERGIN_Y;
			wxImage scaledImg = it->second.Scale(ITEM_W, ITEM_H);

			wxBitmap bmp(scaledImg);
			dc->DrawBitmap(bmp, x, y);
			counter ++;
		}
	}
}

BEGIN_EVENT_TABLE(TextureArea, wxScrolledWindow)
    EVT_SCROLLWIN( TextureArea::OnScroll)
    // end wxGlade
END_EVENT_TABLE()

TextureArea::TextureArea(wxWindow* parent, wxWindowID id):
wxScrolledWindow(parent, id,  wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER|wxTAB_TRAVERSAL)
{
}
TextureArea::~TextureArea()
{
}

void TextureArea::OnScroll(wxScrollWinEvent &event)
{
	wxScrolledWindow::OnScroll(event);
	Refresh();
}
void TextureArea::OnDraw(wxDC& dc)
{
	if(wxGetApp().getShapesManager()->isLoadedShapesFile()){
		//wxBufferedPaintDC dcB(this);
		//wxMemoryDC memDC(dc);

		//親
		TextureDialog* par = (TextureDialog*)GetParent();
		//wxPaintDC dcW(par->panel_13);
		//panel_13->PrepareDC(dcW);
		int colIndex = par->choice_collection->GetSelection();
		if(colIndex >= 0){
			int collection = par->collectionIndexTable[colIndex];
			int clut = par->choice_clut->GetSelection();
	      
			std::map<int, std::map<int, std::map<int, wxImage> > >* tmap = &((MapEditorMainFrame*)par->GetParent())->textureMap;
			drawPanel(collection, clut, &tmap->find(collection)->second[clut], &dc,
				par->panel_13);
		}
	}
}
////////////////////////////////////////////
BEGIN_EVENT_TABLE(TextureDialog, wxDialog)
    // begin wxGlade: TextureDialog::event_table
    EVT_CHOICE(wxID_ANY, TextureDialog::OnType)
    EVT_CHOICE(wxID_ANY, TextureDialog::OnCollection)
    EVT_CHOICE(ID_TYPE, TextureDialog::OnCLUT)
    EVT_PAINT(TextureDialog::OnPaint)
//    EVT_SCROLLWIN( TextureDialog::OnScroll)
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
    panel_13 = new TextureArea(this, ID_SCROLL);
	wxStaticText* label_collection = new wxStaticText(this, wxID_ANY, wxT("Collection"));
	choice_collection = new wxChoice(this, ID_COLLECTION);
	wxStaticText* label_clut = new wxStaticText(this, wxID_ANY, wxT("CLUT"));
	choice_clut = new wxChoice(this, ID_CLUT);

    panel_13->SetMinSize(wxSize(480, 120));
    panel_13->SetMaxSize(wxSize(480, 600));
    panel_13->SetVirtualSize(wxSize(480, 600));
    panel_13->SetScrollRate(10, 10);
    panel_13->SetScrollbars(100, 10, 5, 60);
	panel_13->EnableScrolling(true, true);

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
    if(!wxGetApp().getShapesManager()->isLoadedShapesFile()){
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
		choice_collection->Insert(getString("%d", it->first), counter);
        collectionIndexTable.push_back(it->first);
		counter ++;
	}
    choice_collection->SetSelection(0);

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
	int collection = collectionIndexTable[event.GetSelection()];
	//TODO
    setupDialog(collection);
}
void TextureDialog::OnCLUT(wxCommandEvent &event)
{
	int clut = event.GetSelection();
	//TODO
    setupDialog(collectionIndexTable[choice_collection->GetSelection()]);
}
void TextureDialog::setFloor(bool floor)
{
    this->isFloor_ = floor;
}
void TextureDialog::setupDialog(int collection)
{
    if(wxGetApp().getShapesManager()->isLoadedShapesFile()){
	    std::map<int, std::map<int, std::map<int, wxImage> > >* tmap = &((MapEditorMainFrame*)GetParent())->textureMap;
	    //setup clut choice
	    choice_clut->Clear();
	    std::map<int, std::map<int, wxImage> >::iterator it1;
	    int clutCounter = 0;
        for(it1 = tmap->find(collection)->second.begin(); it1 != tmap->find(collection)->second.end(); it1 ++){
		    choice_clut->Insert(getString("%d", it1->first), clutCounter);
		    clutCounter ++;
	    }
        choice_clut->SetSelection(0);
        choice_30->SetSelection(0);

        //drawPanel(collection, 0, &tmap->find(collection)->second[0]);
        Refresh();
    }
}
int TextureDialog::getIndexSelected()
{
    //選択されたテクスチャ
    //TODO
    return indexSelected;
}

void TextureDialog::OnPaint(wxPaintEvent &event)
{
    wxPaintDC dc(this);

/*    wxPaintDC dcW(panel_13);
	//panel_13->PrepareDC(dcW);
    int colIndex = choice_collection->GetSelection();
    if(colIndex >= 0){
        int collection = collectionIndexTable[colIndex];
        int clut = choice_clut->GetSelection();
      
        std::map<int, std::map<int, std::map<int, wxImage> > >* tmap = &((MapEditorMainFrame*)GetParent())->textureMap;
        drawPanel(collection, clut, &tmap->find(collection)->second[clut], &dcW,
			panel_13);
    }*/
}

/*void TextureDialog::OnScroll(wxScrollWinEvent &event)
{
	wxPaintEvent dummy;
	OnPaint(dummy);
    Refresh();
}*/
