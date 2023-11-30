// #include <ArduinoSTL.h>
// #include <MCUFRIEND_kbv.h>

// enum View { SONG_SELECT, SONG_VIEW };

// class UI {
//  public:
//   MCUFRIEND_kbv tft;
//   View currentView;
//   int scrollTop;
//   std::vector<Song> listItems;

//   UI(MCUFRIEND_kbv& _tft) {
//     tft = _tft;
//     scrollTop = 0;
//   }

//   void setListItems(std::vector<Song>& _listItems) { listItems = _listItems;
//   }

//   void scroll(int dir) { scrollTop += dir; }

//   void firstPage() { tft.fillScreen(TFT_BLACK); }

//   void updateScreen() {
//     if (currentView == View::SONG_SELECT) {
//       renderLibraryPage();
//     } else if (currentView == View::SONG_VIEW) {
//       renderDetailsPage();
//     }

//     diffAreas.clear();
//   }

//  private:
//   std::vector<std::vector<int>> diffAreas;

//   void renderLibraryPage() {}

//   void renderDetailsPage() {}
// };