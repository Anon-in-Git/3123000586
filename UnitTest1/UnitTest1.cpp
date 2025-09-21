#include "pch.h"
#include "CppUnitTest.h"
#include"../Duplication_Checker/Start.h"
#include<vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "汉皇重色思倾国，御宇多年求不得。杨家有女初长成，养在深闺人未识。";
			Ori.push_back(s);
			s = "浔阳江头夜送客，枫叶荻花秋瑟瑟。主人下马客在船，举酒欲饮无管弦。";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			double ans = DC::LCS(Ori, Cmp) * 100;
			Assert::AreEqual(ans, 12.5);
		}
		TEST_METHOD(TestMethod2)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "生活就像海洋，只有意志坚强的人，才能到达彼岸。";
			Ori.push_back(s);
			s = "生活就像天空，只有自强不息的人，才能自由翱翔。";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			double ans = DC::LCS(Ori, Cmp) * 100;
			Assert::AreEqual(ans, 14.0 / 23.0 * 100);
		}
		TEST_METHOD(TestMethod3)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "一位真正的作家永远只为内心写作，只有内心才会真实地告诉他，他的自私、他的高尚是多么突出。内心让他真实地了解自己，一旦了解了自己也就了解了世界。很多年前我就明白了这个原则，可是要捍卫这个原则必须付出艰辛的劳动和长时期的痛苦，因为内心并非时时刻刻都是敞开的，它更多的时候倒是封闭起来，于是只有写作，不停地写作才能使内心敞开，才能使自己置身于发现之中，就像日出的光芒照亮了黑暗，灵感这时候才会突然来到。";
			Ori.push_back(s);
			s = "一位真正丽的作家永远医只为内心写腥作，只怖有惠内陆心才会真实地告诉他，他的自辟私、他船的高尚是多迪么突出。内心让他真实地夯了解自己，一旦了育解了自己也族就了解了疯世界。很多年前碉我就明白了步这耘个粟原则，可是汲要捍涤卫这个原则必须付出艰辛协的劳动和长体时我期召的痛苦，因为内心并非时时刻刻都是敞开的，镍它昂更多的时候倒是位封闭誉起来，于是只有讹写作，不弃停焰地橇写作才能使牵内心敞开，塌才隅能使自己置身于发过现之中，就像日疗出的光芒照亮了黑荒暗，胡灵感鼻这时候才掠会突然来狈到。";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			int ans = DC::LCS(Ori, Cmp) * 10000;
			Assert::AreEqual(ans, 8284);
		}
		TEST_METHOD(TestMethod4)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "一位真正的作家永远只为内心写作，只有内心才会真实地告诉他，他的自私、他的高尚是多么突出。内心让他真实地了解自己，一旦了解了自己也就了解了世界。很多年前我就明白了这个原则，可是要捍卫这个原则必须付出艰辛的劳动和长时期的痛苦，因为内心并非时时刻刻都是敞开的，它更多的时候倒是封闭起来，于是只有写作，不停地写作才能使内心敞开，才能使自己置身于发现之中，就像日出的光芒照亮了黑暗，灵感这时候才会突然来到。";
			Ori.push_back(s);
			s = "一 位真的正作家永远只为内心作写只，有内心才真实地会诉告他，他自的私他、的高尚是多么突出内。心让他真实地了解自己，一旦了解了自也己就了了解界。世很多年前我就明白了这个原则，是可捍要卫这个则原必须付出艰的劳辛动和长时期的痛苦因，为心内并非时刻时刻都是开的敞，它更的多时候倒是封起闭来，于是有只写作不，停写作地才能使内敞心开，才能使自己置身于发现之中，就像日的出芒光照亮黑了暗，灵感这时候才会突然来。到";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			int ans = DC::LCS(Ori, Cmp) * 10000;
			Assert::AreEqual(ans, 8535);
		}
		TEST_METHOD(TestMethod5)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "一位真正的作家永远只为内心写作，只有内心才会真实地告诉他，他的自私、他的高尚是多么突出。内心让他真实地了解自己，一旦了解了自己也就了解了世界。很多年前我就明白了这个原则，可是要捍卫这个原则必须付出艰辛的劳动和长时期的痛苦，因为内心并非时时刻刻都是敞开的，它更多的时候倒是封闭起来，于是只有写作，不停地写作才能使内心敞开，才能使自己置身于发现之中，就像日出的光芒照亮了黑暗，灵感这时候才会突然来到。";
			Ori.push_back(s);
			s = "家 一内前言的作只永远只才位心写地，诉有内心为自私实他告 他，多的会真。作的高尚是他么突出、内心让他真实了了解自己了解旦了解地自己也前我一了世界。很多则就，就明白了这个原年，须是要捍辛这个原和必可期出痛卫的劳动则长时付的艰苦，因是内心并非它时刻的都为倒开的，起更多于时候敞是封闭不来，刻是只能写作，时停地写作使有使内身敞开，才能才自己置心于发现之中，就像日出的这芒照亮会黑暗来灵感光时候才了突然，到。";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			int ans = DC::LCS(Ori, Cmp) * 10000;
			Assert::AreEqual(ans, 6767);
		}
		TEST_METHOD(TestMethod6)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "一位真正的作家永远只为内心写作，只有内心才会真实地告诉他，他的自私、他的高尚是多么突出。内心让他真实地了解自己，一旦了解了自己也就了解了世界。很多年前我就明白了这个原则，可是要捍卫这个原则必须付出艰辛的劳动和长时期的痛苦，因为内心并非时时刻刻都是敞开的，它更多的时候倒是封闭起来，于是只有写作，不停地写作才能使内心敞开，才能使自己置身于发现之中，就像日出的光芒照亮了黑暗，灵感这时候才会突然来到。";
			Ori.push_back(s);
			s = "内心 作的只有内心的会真远地告诉出，他，让私真他作高尚自己么突他。解了自他也实地了解是界，一旦了内心自己、就了解了世多。很要年前我就原白了这个原艰辛的是多和长时个明则必须因出则心可劳动捍卫刻都的痛苦，付为内，的时时倒刻封期是来开的，它有多并非不时是这作起敞，于心只更写作能候停地写身才能使内是敞就像才，使自己照闭于发暗之中，开，日出的光芒置亮了黑现，灵感这时候才来突然来到。";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			int ans = DC::LCS(Ori, Cmp) * 10000;
			Assert::AreEqual(ans, 6236);
		}
		TEST_METHOD(TestMethod7)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "一位真正的作家永远只为内心写作，只有内心才会真实地告诉他，他的自私、他的高尚是多么突出。内心让他真实地了解自己，一旦了解了自己也就了解了世界。很多年前我就明白了这个原则，可是要捍卫这个原则必须付出艰辛的劳动和长时期的痛苦，因为内心并非时时刻刻都是敞开的，它更多的时候倒是封闭起来，于是只有写作，不停地写作才能使内心敞开，才能使自己置身于发现之中，就像日出的光芒照亮了黑暗，灵感这时候才会突然来到。";
			Ori.push_back(s);
			s = "一正作永远只内心写作，只有心才真实地告诉他，他的自私、的高是多突出。内心让他真实地自，一旦了自己也就了解了世界。很多年前我白了这原则，可要捍卫这个原则必付出辛的劳长时期的痛苦，为内心并非时刻刻都是的，它更多的时倒是闭来，于是只有写作，不地写才能使内心敞开，能使自己置发现之，就像日出的光芒亮了暗，灵感这候才会突然来到。";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			int ans = DC::LCS(Ori, Cmp) * 10000;
			Assert::AreEqual(ans, 10000);
		}
		TEST_METHOD(TestMethod8)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "The industrial revolution, which began in Britain in the late 18th century, was a profound transformation of the global economic and social landscape, marked primarily by the shift from agrarian societies to industrialized ones.";
			Ori.push_back(s);
			s = "Beginning in Britain during the late 1700s, the industrial revolution profoundly transformed the global economic and social landscape. This great change was defined by the major shift from agrarian societies to industrialized ones.";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			int ans = DC::LCS(Ori, Cmp) * 10000;
			Assert::AreEqual(ans, 5757);
		}
		TEST_METHOD(TestMethod9)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "The CEO在latest meeting中强调了AI技术是公司的core competitiveness，并计划在未来五年内增加R&D投资。";
			Ori.push_back(s);
			s = "公司的CEO在最新的meeting里指出，人工智能(AI)技术是我们的核心竞争优势(core competitiveness)，我们必须加大研发(R&D)的投入。";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			int ans = DC::LCS(Ori, Cmp) * 10000;
			Assert::AreEqual(ans, 3404);
		}
		TEST_METHOD(TestMethod10)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "998244353.1e7";
			Ori.push_back(s);
			s = "19260817.1e9";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			int ans = DC::LCS(Ori, Cmp) * 10000;
			Assert::AreEqual(ans, 0);
		}
		TEST_METHOD(TestMethod11)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "我昨天买了3个apple，一共花了15.99 yuan，性价比真的很高！My rating: 5 stars.";
			Ori.push_back(s);
			s = "昨日购入了apples共计3个，消费总金额为15.99元，觉得性价比超高！我的评分是5星。";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			int ans = DC::LCS(Ori, Cmp) * 10000;
			Assert::AreEqual(ans, 3783);
		}
		TEST_METHOD(TestMethod12)
		{
			std::vector<std::string> Ori, Cmp;
			std::string s;
			s = "私は昨日、新しいソフトウェアをダウンロードしました。";
			Ori.push_back(s);
			s = "わたしはきのう、あたらしいソフトをダウンロードしました。";
			Cmp.push_back(s);
			DC::Chinese_Process(Ori, Cmp);
			int ans = DC::LCS(Ori, Cmp) * 10000;
			Assert::AreEqual(ans, 6785);
		}
	};

}
