#include "gtest/gtest.h"
#include "../../src/SymbolicArithmetic/RealNumber.h"

using SymbolArithmetic::RealNumber;

TEST(Basic_Operations_Add, zero) {
    EXPECT_EQ("0.0", (RealNumber("0") + RealNumber("0")).ToString());
}

TEST (Basic_Operations_Add, nine) {
    EXPECT_EQ("199999999999999999998.0",
              (RealNumber("99999999999999999999") +
               RealNumber("99999999999999999999")).ToString());
}

TEST (Basic_Operations_Add, randomWholeNumber) {
    EXPECT_EQ("412521857829615973219577583276322091342200904192275215.0",
              (RealNumber("000000001204120005000101000000050130000") +
               RealNumber("00000412521857829615973219576379156317091241200904142145215.0000000")).ToString());
}

TEST (Basic_Operations_Add, randomRealNumber) {
    EXPECT_EQ("4167562197975975129375497513.11413122069517067183222912672157150779214979",
              (RealNumber("4167562197975975129375497512.900002010203912512568359999124120213") +
               RealNumber("0.21412921049125815926386912759745129479214979")).ToString());
}

TEST (Basic_Operations_Add, fractionalTest) {
    EXPECT_EQ("0.9125219471148162631245152112421421",
              (RealNumber("0.91252194710250214") +
               RealNumber("0.0000000000123141231245152112421421")).ToString());
}

TEST (Basic_Operations_Add, secondMinus) {
    EXPECT_EQ("-12330213177884466066000996769968282992927596628099239.0912271213",
              (RealNumber("91299591292131295952219399159214136532163103500132.12399123") +
               RealNumber("-12421512769176597361953216169127497129459759731599371.2152183513")).ToString());
}

TEST (Basic_Operations_Add, firstMinus) {
    EXPECT_EQ("-11304118878712246018196357784553163322417496756998139949991466.00225931830621942572853081506501",
              (RealNumber("-15621975691763571031350170365185316483513510358318153480150601.31751035016253001253153081506501") +
               RealNumber("4317856813051325013153812580632153161096013601320013530159135.3152510318563105868030000000000000")).ToString());
}

TEST (Basic_Operations_Add, bothMinus) {
    EXPECT_EQ("-9513295192395913951935931996364290935715211883212861.312928513606042",
              (RealNumber("-9513295192395913951935931996312969316923573930051510.00031510300501") +
               RealNumber("-51321618791637953161351.312613410601032")).ToString());
}