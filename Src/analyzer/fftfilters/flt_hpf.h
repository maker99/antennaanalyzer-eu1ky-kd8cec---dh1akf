/*
  IIR COEF for +DSP / Audio DSP
  HPF

  by KD8CEC
  kd8cec@gmail.com
  -----------------------------------------------------------------------------
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/


#define FLT_HPF_COUNT 			10
#define FLT_HPF_MINFREQ	  300
#define FLT_HPF_MAXFREQ	  4000

const int FLT_HPF_INDEX[FLT_HPF_COUNT] = {400, 520, 621, 720, 840, 1160, 1480, 1800, 2120, 2440};
const float FLT_HPF[FLT_HPF_COUNT][30] = {
// 400
{
0.74010707943795572827383,
-1.48021415887591145654767,
0.74010707943795572827383,
1.84993237350534345253550,
-0.85565273158402632702746,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.85907626595820985038188,
-0.86482489876726265087825,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.87699936715218052007970,
-0.88280342174755288553456,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.90294457095811564428800,
-0.90882885327333351455081,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.93571483712119807307772,
-0.94170045160372706227747,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.97362286085727656193001,
-0.97972569447328905489769,
}
,
// 520
{
0.67615020024954974875442,
-1.35230040049909949750884,
0.67615020024954974875442,
1.80698406604053252166864,
-0.81644384809921721757320,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.81835702406190957702847,
-0.82787634494346873381687,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.84073830490234047196907,
-0.85037479451987452172546,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.87334742680076371534881,
-0.88315462915012610256582,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.91489421646762636441963,
-0.92491892133008379861536,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.96346274603064574471034,
-0.97374171307128809527143,
}
,
// 621
{
0.62658899161831116408905,
-1.25317798323662232817810,
0.62658899161831116408905,
1.77152189585604946664432,
-0.78477317703860027808815,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.78460964505209407349184,
-0.79795882479579116619561,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.81044880930965779164410,
-0.82399127033985797297078,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.84829494129391402879037,
-0.86212049774493171305778,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.89685910943556756969031,
-0.91104793401719519341242,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.95412692183827618741532,
-0.96874411927074621786460,
}
,
// 720
{
0.58150229143533727071969,
-1.16300458287067454143937,
0.58150229143533727071969,
1.73734720380910090398174,
-0.75485423026779951971577,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.75198175185803051157052,
-0.76963624879317826810166,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.78096329037959111296630,
-0.79890983058657227822152,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.82362541624906882020696,
-0.84200185726386977957958,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.87874435447466403559247,
-0.89767622200857144498798,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.94428930504098951281833,
-0.96388166069223069065686,
}
,
// 840
{
0.53113007992305061311100,
-1.06226015984610122622200,
0.53113007992305061311100,
1.69667071382738554596870,
-0.72001256195892726630348,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.71301344555150891757478,
-0.73658012785909332542644,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.74549367901231033961551,
-0.76950720623242852003187,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.79358825720168790773812,
-0.81826344276888451911844,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.85622871991292814897179,
-0.88176567798293226108086,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.93146587963213089977899,
-0.95803790852742931605235,
}
,
// 1160
{
0.41686866183644050165569,
-0.83373732367288100331137,
0.41686866183644050165569,
1.59195630320003123081563,
-0.63416115087252156179431,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.61205158450530250391353,
-0.65478918441773814596019,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.65234532042837711784955,
-0.69615116008041511008742,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.71289391477921926210115,
-0.75830497700942989247608,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.79338007723137349280762,
-0.84092493309599991579972,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.89256718011866942319443,
-0.94274161605406736619273,
}
,
// 1480
{
0.32681231019619155775402,
-0.65362462039238311550804,
0.32681231019619155775402,
1.49224020599158690991715,
-0.55754348842248646622721,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.51508209889551537230545,
-0.58138498620073242317829,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.56124993952565049859516,
-0.62957321974334201630796,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.63156067184040054485195,
-0.70296088403716461279203,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.72680476581899999821701,
-0.80237304153796795702647,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.84706740120290113793544,
-0.92789859961543130761896,
}
,
// 1800
{
0.25583249015846926122109,
-0.51166498031693852244217,
0.25583249015846926122109,
1.39699536244133648565935,
-0.48903033843062476693220,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.42174925243967797960920,
-0.51541503103067098923162,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.47214247233060935293736,
-0.56912818948931520601775,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.54982940876210339986585,
-0.65193319253819503877878,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.65691841993308641711735,
-0.76607729840513616448305,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.79527683704971718903209,
-0.91355085930792234716336,
}
,
// 2120
{
0.19990550120710848247541,
-0.39981100241421696495081,
0.19990550120710848247541,
1.30575681026283740848726,
-0.42766956968754837875579,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.33172774729733567333767,
-0.45606529866939543582660,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.38494234555283113330404,
-0.51424830946849375834518,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.46789399594937797211003,
-0.60494478992772393599608,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.58409797665434060043310,
-0.73199822424650784480349,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.73751285665196064655902,
-0.89973677555131081895468,
}
,
// 2440
{
0.15586714385278924166478,
-0.31173428770557848332956,
0.15586714385278924166478,
1.21811223658095357791353,
-0.37265469733137607244444,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.24471970457010927546548,
-0.40263786704480314382337,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.29955822890690808613101,
-0.46443378023332082538133,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.38590850972733292678640,
-0.56173936097088228436292,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.50868407623987033083779,
-0.70009152018076581391881,
1.00000000000000000000000,
-2.00000000000000000000000,
1.00000000000000000000000,
1.67409772345623930611680,
-0.88649127304062824705966,
}

};

