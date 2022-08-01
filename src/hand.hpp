#ifndef HAND_HPP_
#define HAND_HPP_

#include <memory>
#include <vector>
#include "cards.hpp"
#include "hand_summary.cpp"
#include "table.cpp"
#include "uecda_common.hpp"

class Hand {
 public:
  /* 配列形式のカードから手を生成。 */
  Hand(uecda_common::CommunicationBody src);

  /* ビットカードから手を生成。 */
  Hand(Cards::bitcards src, Cards::bitcards joker_src, HandSummary* hs);

  ~Hand() {
    delete this->cards;
    delete this->joker;
    delete this->summary;
  }

  /* 与えられた状況に対して合法手か？ */
  bool isLegal(Table* tbl, Hand* table_hand);

  /* 手のサマリを返す。 */
  HandSummary getSummary() { return *(this->summary); }

  /* 与えられたベクターに、与えられたカードから生成できる手をすべて追加する。 */
  static void pushHands(Cards* src, std::vector<Hand*>* hand_vec);

  /* 与えられた配列に手の構成カードを置く。 */
  void putCards(uecda_common::CommunicationBody dst);

 private:
  static const int kPairFilterSize[4];
  static const Cards::bitcards pairFilters[4][6];
  /* 順に1枚, 2枚, 3枚, 4枚, ..., 14枚の階段用。 */
  static const Cards::bitcards sequenceFilters[14];

  Cards* cards;
  Cards* joker;
  HandSummary* summary;

  /* 与えられたカードを手とみなしてサマリを作る。 */
  static HandSummary* summarize(Cards::bitcards src, Cards::bitcards joker_src);

  /* ジョーカーなしで与えられた配列に指定された枚数の枚数組を作る。 */
  static void pushPair(Cards::bitcards src, std::vector<Hand*>* hand_vec,
                       int pair_qty);

  /* ジョーカー必ず込みで与えられた配列に指定された枚数の枚数組を作る。 */
  static void pushPairWithJoker(Cards::bitcards src,
                                std::vector<Hand*>* hand_vec, int pair_qty);

  /* ジョーカーなしで与えられた配列に指定された枚数の階段を作る。 */
  static void pushSequence(Cards::bitcards src, std::vector<Hand*>* hand_vec,
                           int seq_qty);

  /* ジョーカー必ず込みで与えられた配列に指定された枚数の階段を作る。 */
  static void pushSequenceWithJoker(Cards::bitcards src,
                                    std::vector<Hand*>* hand_vec, int seq_qty);
};

#endif  // HANDS_HPP_
