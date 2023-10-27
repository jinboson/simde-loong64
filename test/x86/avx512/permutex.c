/* SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Copyright:
 *   2023      Michael R. Crusoe <crusoe@debian.org>
 */

#define SIMDE_TEST_X86_AVX512_INSN permutex

#include <test/x86/avx512/test-avx512.h>
#include <simde/x86/avx512/set.h>
#include <simde/x86/avx512/permutex.h>

static int
test_simde_mm256_permutex_epi64(SIMDE_MUNIT_TEST_ARGS) {
#if 1
  const struct {
    int64_t a[4];
    int64_t r[4];
  } test_vec[8] = {
    { {  INT64_C( 3380730272638549406), -INT64_C( 9153520704702256789),  INT64_C( 9176172621361943730), -INT64_C(  224897000177715056) },
      {  INT64_C( 3380730272638549406),  INT64_C( 3380730272638549406),  INT64_C( 3380730272638549406),  INT64_C( 3380730272638549406) } },
    { {  INT64_C( 1743540307420702910),  INT64_C( 1594468214328802101), -INT64_C( 1070409334618582716),  INT64_C( 4591284037861212252) },
      {  INT64_C( 1594468214328802101),  INT64_C( 1743540307420702910),  INT64_C( 1743540307420702910),  INT64_C( 1743540307420702910) } },
    { { -INT64_C( 7191838048563029396), -INT64_C( 2438034435728414288),  INT64_C( 8629363194122729070),  INT64_C( 6118960229233353769) },
      {  INT64_C( 8629363194122729070), -INT64_C( 7191838048563029396), -INT64_C( 7191838048563029396), -INT64_C( 7191838048563029396) } },
    { {  INT64_C( 5910585981377785091),  INT64_C(  936626256355934855),  INT64_C( 6059766109351740039),  INT64_C( 3980592959627086337) },
      {  INT64_C( 3980592959627086337),  INT64_C( 5910585981377785091),  INT64_C( 5910585981377785091),  INT64_C( 5910585981377785091) } },
    { { -INT64_C( 3383989709936940267), -INT64_C( 8677045597436219415),  INT64_C( 1076994787638800499), -INT64_C( 1155395570052370037) },
      { -INT64_C( 3383989709936940267), -INT64_C( 3383989709936940267), -INT64_C( 3383989709936940267), -INT64_C( 3383989709936940267) } },
    { {  INT64_C( 3024923889355888864),  INT64_C( 5883467878739602463), -INT64_C( 7218458691070079050), -INT64_C( 2334180723799635245) },
      {  INT64_C( 5883467878739602463),  INT64_C( 3024923889355888864),  INT64_C( 3024923889355888864),  INT64_C( 3024923889355888864) } },
    { {  INT64_C( 1248627335310623466),  INT64_C(  152796157942236655), -INT64_C( 4444321726930219610), -INT64_C( 1639298172395213470) },
      { -INT64_C( 4444321726930219610),  INT64_C( 1248627335310623466),  INT64_C( 1248627335310623466),  INT64_C( 1248627335310623466) } },
    { {  INT64_C( 4274030723042920780), -INT64_C(   19379610889715347),  INT64_C( 8999888709901189428), -INT64_C( 6008612931454020172) },
      { -INT64_C( 6008612931454020172),  INT64_C( 4274030723042920780),  INT64_C( 4274030723042920780),  INT64_C( 4274030723042920780) } },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r, a = simde_mm256_loadu_epi64(test_vec[i].a);
    SIMDE_CONSTIFY_4_(simde_mm256_permutex_epi64, r, (HEDLEY_UNREACHABLE(), a), i & 3, a);
    simde_test_x86_assert_equal_i64x4(r, simde_mm256_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m256i r, a = simde_test_x86_random_i64x4();
    SIMDE_CONSTIFY_4_(simde_mm256_permutex_epi64, r, (HEDLEY_UNREACHABLE(), a), i & 3, a);

    simde_test_x86_write_i64x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm512_permutex_epi64(SIMDE_MUNIT_TEST_ARGS) {
#if 1
  const struct {
    int64_t a[8];
    int64_t r[8];
  } test_vec[8] = {
    { {  INT64_C( 7111032946101335276),  INT64_C( 6531688641137234627),  INT64_C( 7787813351878868649), -INT64_C( 3220229969086318870),
         INT64_C(  130996079200421797),  INT64_C( 2469692755643154870), -INT64_C( 2935619158353571878), -INT64_C( 2070041481608049525) },
      {  INT64_C( 7111032946101335276),  INT64_C( 7111032946101335276),  INT64_C( 7111032946101335276),  INT64_C( 7111032946101335276),
         INT64_C(  130996079200421797),  INT64_C(  130996079200421797),  INT64_C(  130996079200421797),  INT64_C(  130996079200421797) } },
    { {  INT64_C( 1495796916117764740),  INT64_C( 3458842952237857124), -INT64_C( 6766015125913173418), -INT64_C( 4019926367883393259),
         INT64_C( 1137243206246303829),  INT64_C( 7281456449432963205),  INT64_C( 8154263398216372848), -INT64_C( 1272554307253420470) },
      {  INT64_C( 3458842952237857124),  INT64_C( 1495796916117764740),  INT64_C( 1495796916117764740),  INT64_C( 1495796916117764740),
         INT64_C( 7281456449432963205),  INT64_C( 1137243206246303829),  INT64_C( 1137243206246303829),  INT64_C( 1137243206246303829) } },
    { { -INT64_C( 5675545791928606590), -INT64_C( 8599736633982637518),  INT64_C( 6735194892811587499), -INT64_C( 5116579326666785673),
         INT64_C( 4323210491161059106), -INT64_C( 3320521656765739957), -INT64_C( 6133251560306050445),  INT64_C( 3637422031181106828) },
      {  INT64_C( 6735194892811587499), -INT64_C( 5675545791928606590), -INT64_C( 5675545791928606590), -INT64_C( 5675545791928606590),
        -INT64_C( 6133251560306050445),  INT64_C( 4323210491161059106),  INT64_C( 4323210491161059106),  INT64_C( 4323210491161059106) } },
    { { -INT64_C( 3703226079230533801), -INT64_C( 5908129820114479092), -INT64_C( 5264120643586827755), -INT64_C( 4888953830051894044),
         INT64_C( 3647555225090041425), -INT64_C(   91647695598137904), -INT64_C( 1647973297498427840), -INT64_C( 2448264346831316251) },
      { -INT64_C( 4888953830051894044), -INT64_C( 3703226079230533801), -INT64_C( 3703226079230533801), -INT64_C( 3703226079230533801),
        -INT64_C( 2448264346831316251),  INT64_C( 3647555225090041425),  INT64_C( 3647555225090041425),  INT64_C( 3647555225090041425) } },
    { { -INT64_C( 6196303435597339990),  INT64_C(  865378099963258395),  INT64_C( 7443211590141691998), -INT64_C( 2909968377094002381),
        -INT64_C( 5233558131230356007), -INT64_C( 2095935773227674608),  INT64_C( 3237684583516692485),  INT64_C( 3440338171692097465) },
      { -INT64_C( 6196303435597339990), -INT64_C( 6196303435597339990), -INT64_C( 6196303435597339990), -INT64_C( 6196303435597339990),
        -INT64_C( 5233558131230356007), -INT64_C( 5233558131230356007), -INT64_C( 5233558131230356007), -INT64_C( 5233558131230356007) } },
    { {  INT64_C( 2389513715711174359), -INT64_C( 6359673515922299818),  INT64_C( 5507089338106511943), -INT64_C( 5097808824929920581),
        -INT64_C( 4861541899440479145), -INT64_C( 5511749067919096262), -INT64_C( 8703380222127067049), -INT64_C( 5596046499468776774) },
      { -INT64_C( 6359673515922299818),  INT64_C( 2389513715711174359),  INT64_C( 2389513715711174359),  INT64_C( 2389513715711174359),
        -INT64_C( 5511749067919096262), -INT64_C( 4861541899440479145), -INT64_C( 4861541899440479145), -INT64_C( 4861541899440479145) } },
    { {  INT64_C( 1233883868887089917),  INT64_C( 7154090107906930472),  INT64_C( 6301808691919076384), -INT64_C( 2090714877852971793),
        -INT64_C( 2327123268051069493),  INT64_C( 3570153911500448028),  INT64_C( 5615022670838880760), -INT64_C(  835818874319937634) },
      {  INT64_C( 6301808691919076384),  INT64_C( 1233883868887089917),  INT64_C( 1233883868887089917),  INT64_C( 1233883868887089917),
         INT64_C( 5615022670838880760), -INT64_C( 2327123268051069493), -INT64_C( 2327123268051069493), -INT64_C( 2327123268051069493) } },
    { {  INT64_C( 3188632169402051497),  INT64_C( 7507465879757829357),  INT64_C( 8963827773462105529),  INT64_C( 4172134877510041032),
        -INT64_C( 5238008759181476591),  INT64_C( 4352418444976956302),  INT64_C( 1481044688329007922),  INT64_C(  324801177760206263) },
      {  INT64_C( 4172134877510041032),  INT64_C( 3188632169402051497),  INT64_C( 3188632169402051497),  INT64_C( 3188632169402051497),
         INT64_C(  324801177760206263), -INT64_C( 5238008759181476591), -INT64_C( 5238008759181476591), -INT64_C( 5238008759181476591) } },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m512i r, a = simde_mm512_loadu_epi64(test_vec[i].a);
    SIMDE_CONSTIFY_4_(simde_mm512_permutex_epi64, r, (HEDLEY_UNREACHABLE(), a), i & 3, a);
    simde_test_x86_assert_equal_i64x8(r, simde_mm512_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m512i r, a = simde_test_x86_random_i64x8();
    SIMDE_CONSTIFY_4_(simde_mm512_permutex_epi64, r, (HEDLEY_UNREACHABLE(), a), i & 3, a);

    simde_test_x86_write_i64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DIAGNOSTIC_DISABLE_UNREACHABLE_

static int
test_simde_mm512_mask_permutex_epi64(SIMDE_MUNIT_TEST_ARGS) {
#if 1
  const struct {
    int64_t src[8];
    simde__mmask8 k;
    int64_t a[8];
    int64_t r[8];
  } test_vec[8] = {
    { { -INT64_C( 7486586679393816934), -INT64_C( 8343033559076131759),  INT64_C( 1197459257425703975), -INT64_C( 6713388164491843233),
         INT64_C(  169843424140027055),  INT64_C( 3732820038704264467),  INT64_C( 4774229997178759512),  INT64_C( 6344631420636588129) },
      UINT8_C(183),
      { -INT64_C( 3116078896968410867),  INT64_C( 3039054343813017324), -INT64_C( 2255567292687776116),  INT64_C( 4253181656590615813),
        -INT64_C( 8988135271719951953), -INT64_C( 3970863992653719064), -INT64_C( 2157527836284927826),  INT64_C( 6762601992202246256) },
      { -INT64_C( 3116078896968410867), -INT64_C( 3116078896968410867), -INT64_C( 3116078896968410867), -INT64_C( 6713388164491843233),
        -INT64_C( 8988135271719951953), -INT64_C( 8988135271719951953),  INT64_C( 4774229997178759512), -INT64_C( 8988135271719951953) } },
    { {  INT64_C( 7599492389766352083),  INT64_C( 6171177330504183886),  INT64_C( 4035529695841931942),  INT64_C( 5544286804228087972),
         INT64_C( 6883840064914865935),  INT64_C( 4749884303147871616), -INT64_C( 3106125636967457588),  INT64_C( 2033937142011316851) },
      UINT8_C(168),
      { -INT64_C( 1967857106333985985), -INT64_C( 3760957590054828558), -INT64_C( 1763903126588907392), -INT64_C( 3292397876720397275),
         INT64_C( 4713249348516023073), -INT64_C( 4133288204896902440), -INT64_C( 7162977996100920516), -INT64_C( 7352375464808256623) },
      {  INT64_C( 7599492389766352083),  INT64_C( 6171177330504183886),  INT64_C( 4035529695841931942), -INT64_C( 1967857106333985985),
         INT64_C( 6883840064914865935),  INT64_C( 4713249348516023073), -INT64_C( 3106125636967457588),  INT64_C( 4713249348516023073) } },
    { {  INT64_C( 7549503602037366298),  INT64_C( 6692759446045498632), -INT64_C( 7819816680974806548), -INT64_C( 5763581032929714371),
         INT64_C( 4373666164843084739), -INT64_C( 4423165037818847232),  INT64_C( 1949538425697431379), -INT64_C( 9148085459099510331) },
      UINT8_C( 29),
      {  INT64_C(  784889719804373107), -INT64_C( 2705000331639798307),  INT64_C(  815542160741179480), -INT64_C( 5567169047966595459),
        -INT64_C( 2148710680891848679), -INT64_C( 5015309716648789500), -INT64_C( 7170503428392567765),  INT64_C( 7996586806883181320) },
      {  INT64_C(  815542160741179480),  INT64_C( 6692759446045498632),  INT64_C(  784889719804373107),  INT64_C(  784889719804373107),
        -INT64_C( 7170503428392567765), -INT64_C( 4423165037818847232),  INT64_C( 1949538425697431379), -INT64_C( 9148085459099510331) } },
    { {  INT64_C( 4293905999164772948),  INT64_C( 5102394255324554138), -INT64_C( 6804373069614464696),  INT64_C( 2777707024676739546),
         INT64_C( 5544865394268417783),  INT64_C( 3550174517511950708), -INT64_C( 8763637995539813887), -INT64_C( 5467508773957052634) },
      UINT8_C( 97),
      { -INT64_C( 7048590629501347537), -INT64_C( 2230440838870261775),  INT64_C( 4304598005180319627),  INT64_C( 7118312164899992153),
        -INT64_C( 8649881519277197780), -INT64_C(   49138877861883247),  INT64_C( 5513519694557409843),  INT64_C( 3980103496302245798) },
      {  INT64_C( 7118312164899992153),  INT64_C( 5102394255324554138), -INT64_C( 6804373069614464696),  INT64_C( 2777707024676739546),
         INT64_C( 5544865394268417783), -INT64_C( 8649881519277197780), -INT64_C( 8649881519277197780), -INT64_C( 5467508773957052634) } },
    { {  INT64_C( 1478164203594812800),  INT64_C( 3999063725834826975),  INT64_C(   96958554672187325), -INT64_C( 1196194511210138919),
        -INT64_C( 4870812475003412784),  INT64_C( 3807379478515609433),  INT64_C( 5952418920687534415), -INT64_C( 4986120395978987665) },
      UINT8_C(  6),
      {  INT64_C( 7833014380530609691), -INT64_C( 7921865537967375260), -INT64_C( 6796838718533733150), -INT64_C( 2588922442487495826),
        -INT64_C(  469631562349797125),  INT64_C( 5267772747979982404),  INT64_C( 8911304304625927896),  INT64_C( 8282654588835933011) },
      {  INT64_C( 1478164203594812800),  INT64_C( 7833014380530609691),  INT64_C( 7833014380530609691), -INT64_C( 1196194511210138919),
        -INT64_C( 4870812475003412784),  INT64_C( 3807379478515609433),  INT64_C( 5952418920687534415), -INT64_C( 4986120395978987665) } },
    { { -INT64_C( 9037997690807680571),  INT64_C( 8873272370331720297),  INT64_C(  394351777350758101),  INT64_C( 4955348817655139800),
         INT64_C( 6696330323863691120), -INT64_C( 2382460237360015553),  INT64_C( 6186676492538509564), -INT64_C( 5274322890633554166) },
      UINT8_C( 67),
      { -INT64_C( 4429835027955425482), -INT64_C(  518152564320620569),  INT64_C( 6516894822334124958), -INT64_C( 7998761986363784447),
         INT64_C( 1753378211606700047),  INT64_C( 5792993281516866671), -INT64_C( 2497847576637984085), -INT64_C(  483254147766535840) },
      { -INT64_C(  518152564320620569), -INT64_C( 4429835027955425482),  INT64_C(  394351777350758101),  INT64_C( 4955348817655139800),
         INT64_C( 6696330323863691120), -INT64_C( 2382460237360015553),  INT64_C( 1753378211606700047), -INT64_C( 5274322890633554166) } },
    { {  INT64_C( 7905098145102859269), -INT64_C( 5325382849591828587), -INT64_C( 6766535940265339940),  INT64_C( 2592248327974933395),
        -INT64_C( 8115736143658980080), -INT64_C( 3786095792272670917),  INT64_C(  663045603214952232),  INT64_C( 6102580095367495535) },
      UINT8_C(117),
      {  INT64_C( 8047551227439224869), -INT64_C( 1666714771024598492),  INT64_C( 7866291006134117034), -INT64_C( 4106250819517879956),
         INT64_C( 1397687017728788930), -INT64_C( 2096982838449040321),  INT64_C( 8778127059739369575),  INT64_C( 4071021476573662230) },
      {  INT64_C( 7866291006134117034), -INT64_C( 5325382849591828587),  INT64_C( 8047551227439224869),  INT64_C( 2592248327974933395),
         INT64_C( 8778127059739369575),  INT64_C( 1397687017728788930),  INT64_C( 1397687017728788930),  INT64_C( 6102580095367495535) } },
    { {  INT64_C( 2898480416440987238),  INT64_C( 9082706148361975967),  INT64_C( 1190643843478548804),  INT64_C( 2652268054834527789),
         INT64_C( 5380210198493148142), -INT64_C( 8129566549369550448), -INT64_C( 1531075724029478804), -INT64_C(  745889964335347772) },
      UINT8_C( 80),
      { -INT64_C( 5964699819020139196), -INT64_C( 8213290138837768150),  INT64_C( 5686075501991298113), -INT64_C( 9132605993466647738),
         INT64_C(  362164674830055740),  INT64_C( 3135490412680733394),  INT64_C(  530036897698398595), -INT64_C( 2235307532370039748) },
      {  INT64_C( 2898480416440987238),  INT64_C( 9082706148361975967),  INT64_C( 1190643843478548804),  INT64_C( 2652268054834527789),
        -INT64_C( 2235307532370039748), -INT64_C( 8129566549369550448),  INT64_C(  362164674830055740), -INT64_C(  745889964335347772) } },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m512i r,
      src = simde_mm512_loadu_epi64(test_vec[i].src),
      a = simde_mm512_loadu_epi64(test_vec[i].a);
    switch(i & 3) {
      case 0: r = simde_mm512_mask_permutex_epi64(src, test_vec[i].k, a, 0); break;
      case 1: r = simde_mm512_mask_permutex_epi64(src, test_vec[i].k, a, 1); break;
      case 2: r = simde_mm512_mask_permutex_epi64(src, test_vec[i].k, a, 2); break;
      case 3: r = simde_mm512_mask_permutex_epi64(src, test_vec[i].k, a, 3); break;
      default: HEDLEY_UNREACHABLE(); r = simde_mm512_setzero_si512(); break;
    }
    simde_test_x86_assert_equal_i64x8(r, simde_mm512_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m512i r,
      src = simde_test_x86_random_i64x8(),
      a = simde_test_x86_random_i64x8();
    simde__mmask8 k = simde_test_x86_random_mmask8();
    SIMDE_CONSTIFY_4_(simde_mm512_mask_permutex_epi64, r, (HEDLEY_UNREACHABLE(), a), i & 3, src, k, a);

    simde_test_x86_write_i64x8(2, src, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_mmask8(2, k, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x8(2, a, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}
HEDLEY_DIAGNOSTIC_POP //_DISABLE_UNREACHABLE_

SIMDE_TEST_FUNC_LIST_BEGIN
  SIMDE_TEST_FUNC_LIST_ENTRY(mm256_permutex_epi64)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm512_permutex_epi64)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm512_mask_permutex_epi64)
SIMDE_TEST_FUNC_LIST_END

#include <test/x86/avx512/test-avx512-footer.h>