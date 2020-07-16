#include "gtest/gtest.h"
#include "../../src/SymbolicArithmetic/RealNumber.h"

using SymbolArithmetic::RealNumber;

TEST(Basic_Operations_Mul, zero) {
    EXPECT_EQ("0.0", (RealNumber("0") * RealNumber("0")).ToString());
}

TEST (Basic_Operations_Mul, nine) {
    EXPECT_EQ("9999999999999999999800000000000000000001.0",
              (RealNumber("99999999999999999999") *
               RealNumber("99999999999999999999")).ToString());
}

TEST (Basic_Operations_Mul, randomWholeNumber) {
    EXPECT_EQ("496725821512448139528897646701614607549972574291746884463628353068039645739627950000.0",
              (RealNumber("000000001204120005000101000000050130000") *
               RealNumber("00000412521857829615973219576379156317091241200904142145215.0000000")).ToString());
}

TEST (Basic_Operations_Mul, randomRealNumber) {
    EXPECT_EQ("892396803125808087428185145.46907312300929808966986156661610801423765593700303533119130727281897763266270527",
              (RealNumber("4167562197975975129375497512.900002010203912512568359999124120213") *
               RealNumber("0.21412921049125815926386912759745129479214979")).ToString());
}

TEST (Basic_Operations_Mul, fractionalTest) {
    EXPECT_EQ("0.000000000011236907610442567966282093157540323434094",
              (RealNumber("0.91252194710250214") *
               RealNumber("0.0000000000123141231245152112421421")).ToString());
}

TEST (Basic_Operations_Mul, secondMinus) {
    EXPECT_EQ("-1134079039055813368864608494130749778507272003489621255915961479422591040270684527590861549582556800437.572573889696259099",
              (RealNumber("91299591292131295952219399159214136532163103500132.12399123") *
               RealNumber("-12421512769176597361953216169127497129459759731599371.2152183513")).ToString());
}

TEST (Basic_Operations_Mul, firstMinus) {
    EXPECT_EQ("-67453454174003521270793075371859508613904019819460221515871084775697464400022102285243061922999184625342585301837059163041.10357801455409714307155076127783883031350558569306303",
              (RealNumber("-15621975691763571031350170365185316483513510358318153480150601.31751035016253001253153081506501") *
               RealNumber("4317856813051325013153812580632153161096013601320013530159135.3152510318563105868030000000000000")).ToString());
}

TEST (Basic_Operations_Mul, bothMinus) {
    EXPECT_EQ("488237709316465134530151415435382473783656394739899807706274731275724143824.61050381595191681017340717032",
              (RealNumber("-9513295192395913951935931996312969316923573930051510.00031510300501") *
               RealNumber("-51321618791637953161351.312613410601032")).ToString());
}

TEST (Basic_Operations_Mul, bigLessMul) {
    EXPECT_EQ("42294501605992379080645537111420201183531837.01629490043317220055992927375706811645001421868002792383009819564859978277942354376",
              (RealNumber("412979173561098904760096910599606531560480601650308651802605210.41830650381620856108041108331085608") *
               RealNumber("00000000.000000000000000000102413158613517945975397971397")).ToString());
}

TEST (Basic_Operations_Mul, LessLessMul) {
    EXPECT_EQ("0.00000000000000000000000000000000000000000000016804411832867474027925050377413296552357235469495734980472174277935589227153133817625181",
              (RealNumber("0.0001351808010005002135000326104810816499991313333774777172231751") *
               RealNumber("0.0000000000000000000000000000000000000000012431063959152965936193615931")).ToString());
}