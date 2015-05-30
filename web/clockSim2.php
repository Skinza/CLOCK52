<!DOCTYPE html>
<html>
	<head>
		<title>Clock 52 Sim test 2</title>
		<link href='http://fonts.googleapis.com/css?family=Source+Code+Pro' rel='stylesheet' type='text/css'>
	</head>
	<body onload="startClock52()">
		<style type="text/css">
			#clock52 {
				background: black;
				width: 400px;
				height: 400px;
				font-family: 'Source Code Pro';
                                font-weight: bold;

			}
			

			/* minuut 1 */
			#clock52 .minuutIndicator {
				width: 10px;
				height: 10px;
				position: absolute;
				color: white;
				text-align: center;
				line-height: 10px;
			}

			#clock52 #LED-121 {
				left: 20px;
				top: 20px;
			}

			#clock52 #LED-122 {
				left: 385px;
				top: 20px;
			}

			 #clock52 #LED-123 {
                                left: 385px;
                                top: 385px;
                        }

			 #clock52 #LED-124 {
                                left: 20px;
                                top: 385px;
                        }


		
			#clock52 #clock52grid {
				position: absolute;
				text-align: center;
				margin: 50px 50px 50px 50px;
				width: 300px;
				height: 300px;
				font-family: 'Source Code Pro';
				font-weight: bold;
				color: white;
			}

			#uurTxt,#minuutTxt { 
				width: 50px;
			}
			
		</style>
		<?php
			error_reporting(-1);
			ini_set('display_errors', 'On');
			
			
			$letters = 	"HETKISAVIJF" .
					"TIENBTZVOOR" .
					"OVERMEKWART" .
					"HALFSPWOVER" .
					"VOORTHGEENS" .
					"TWEEPVCDRIE" .
					"VIERVIJFZES" .
					"ZEVENONEGEN" .
					"ACHTTIENELF" .
					"TWAALFBFUUR" .
					"1234567890X";
			$config['lettersPerRow'] = 11;
			$gridLEDcountStart = 0;
			$letterLength = strlen($letters);
			?>
			<div id="clock52">
				<div id="LED-121" class="minuutIndicator">&#149;</div>
				<div id="LED-122" class="minuutIndicator">&#149;</div>
				<div id="LED-123" class="minuutIndicator">&#149;</div>
				<div id="LED-124" class="minuutIndicator">&#149;</div>
				<table id="clock52grid">
					<tr>
						<?php
						for($i = 0; $i < $letterLength; $i++) {
							echo "<td class=\"clock52letter\" id=\"LED-".($i+$gridLEDcountStart)."\">".$letters[$i]."</td>";
							if($i>0 && ($i+1)%$config['lettersPerRow'] == 0) {
								echo "</tr>\n</tr>";
							}
						}
						?>
					</tr>
				</table>
			</div>
			Uur: <input type="text" disabled="disabled" id="uurTxt" /><input type="button" value="+" disabled="disabled" id="uurPlus" onClick="uurPlus()" /><input type="button" value="-" disabled="disabled" id="uurMin" onClick="uurMin()" /><br />
			Minuut: <input type="text" disabled="disabled" id="minuutTxt" /><input type="button" value="+" disabled="disabled" id="minuutPlus" onClick="minuutPlus()" /><input type="button" value="-" disabled="disabled" id="minuutMin" onClick="minuutMin()" /><br />
			<input type="button" id="toggleManual" value="Handmatig" onclick="toggleManual()" /> 
			<script type="text/javascript">
				var isManual = false;

				function uurPlus() { 
					var elem = document.getElementById('uurTxt');
					var val = parseInt(elem.value)+1;
					if(val > 23) { val = 0; }
					elem.value = val;
					updateClock52();
				}

				function minuutPlus() {
                                        var elem = document.getElementById('minuutTxt');
                                        var val = parseInt(elem.value)+1;
					if(val > 59) { val = 0; }
					elem.value = val;
					updateClock52();
                                }

				function uurMin() {
                                        var elem = document.getElementById('uurTxt');
                                        var val = parseInt(elem.value)-1;
					if(val < 0) { val = 23; }
					elem.value = val;
					updateClock52();
                                }

                                function minuutMin() {
                                        var elem = document.getElementById('minuutTxt');
                                        var val = parseInt(elem.value)-1;
					if(val < 0) { val = 59; }
					elem.value = val;
					updateClock52();
                                }


				function toggleManual() {
					if(isManual) {
						document.getElementById('toggleManual').value="Handmatig";
						document.getElementById('uurPlus').disabled="disabled";
						document.getElementById('uurMin').disabled="disabled";
						document.getElementById('minuutPlus').disabled="disabled";
						document.getElementById('minuutMin').disabled="disabled";
					} else {
						document.getElementById('toggleManual').value="Automatisch";
						document.getElementById('uurPlus').disabled="";
                                                document.getElementById('uurMin').disabled="";
                                                document.getElementById('minuutPlus').disabled="";
                                                document.getElementById('minuutMin').disabled="";

					}
					isManual = !isManual;
					updateClock52();
				}
				function startClock52() {
					/*for(var i=0;i < 121; i++) {
						setPixel(i,100,100,100);
					}
					setHETIS(255,255,255);*/
				
					updateClock52();
					setTimeout(startClock52,500);
				}

				

				function updateClock52() {
					//clear display
					for(var i=0;i < 125; i++) {
                                                setPixel(i,100,100,100);
                                        }
					// zet het is weer aan
                                        setHETIS(255,255,255);
					
					if(!isManual) {// vraag datum op
						var today=new Date();
						var h=today.getHours();
						var m=today.getMinutes();
						var s=today.getSeconds();

						document.getElementById('uurTxt').value=h;
						document.getElementById('minuutTxt').value=m;
						

						// seconde pulse
						if(s%2 == 0) {
							setPixel(120,255,255,255);
						} else {
							setPixel(120,100,100,100);
						}
					} else {
						// zet pulse uit
						setPixel(120,100,100,100);
						var h = parseInt(document.getElementById('uurTxt').value);
						var m = parseInt(document.getElementById('minuutTxt').value);
						var s = 0;
					}

					//console.log("minuut = " + m);

					//zet uur
					//als het aantal minuten >=20 dan uur + 1
					if(m >=20) { h = h + 1; }

					//console.log("uur = " + h);
					switch(h) {
						case 0: 
						case 12:
						case 24:
							setUurTwaalf(255,255,255);
							break;
						case 1:
						case 13:
							setUurEen(255,255,255);
							break;
						case 2:
						case 14:
							setUurTwee(255,255,255);
							break;
						case 3:
						case 15:
							setUurDrie(255,255,255);
							break;
						case 4:
						case 16:
							setUurVier(255,255,255);
							break;
						case 5:
						case 17:
							setUurVijf(255,255,255);
							break;
						case 6:
						case 18:
							setUurZes(255,255,255);
							break;
						case 7:
						case 19:
							setUurZeven(255,255,255);
							break;
						case 8:
						case 20:
							setUurAcht(255,255,255);
							break;
						case 9:
						case 21:
							setUurNegen(255,255,255);
							break;
						case 10:
						case 22:
							setUurTien(255,255,255);
							break;
						case 11:
						case 23:
							setUurElf(255,255,255);
							break;	
						
					}

					// parse minuut
					if(m < 5) { setUur(255,255,255); }
					else if(m < 10) { setMinuutVijf(255,255,255); setOver2(255,255,255); console.log("test")}
					else if(m < 15) { setMinuutTien(255,255,255); setOver2(255,255,255); }
					else if(m < 20) { setKwart(255,255,255); setOver2(255,255,255); }
					else if(m < 25) { setMinuutTien(255,255,255); setVoor1(255,255,255); setHalf(255,255,255); }
					else if(m < 30) { setMinuutVijf(255,255,255); setVoor1(255,255,255); setHalf(255,255,255); }
					else if(m < 35) { setHalf(255,255,255); }
					else if(m < 40) { setMinuutVijf(255,255,255); setOver1(255,255,255); setHalf(255,255,255); }
					else if(m < 45) { setMinuutTien(255,255,255); setOver1(255,255,255); setHalf(255,255,255); }
					else if(m < 50) { setKwart(255,255,255); setVoor2(255,255,255); }
					else if(m < 55) { setMinuutTien(255,255,255); setVoor2(255,255,255); }
					else { setMinuutVijf(255,255,255); setVoor2(255,255,255); }

					var modMinuut = m%5;
					console.log(modMinuut);
					if(modMinuut >= 4) { setPixel(124,255,255,255); }
					if(modMinuut >= 3) { setPixel(123,255,255,255); }
					if(modMinuut >= 2) { setPixel(122,255,255,255); }
					if(modMinuut >= 1) { setPixel(121,255,255,255); }
					
					
					//setTimeout(updateClock52,500);
				}

				function setHETIS(red,green,blue) {
					setPixel(0,red,green,blue);
					setPixel(1,red,green,blue);
					setPixel(2,red,green,blue);
					setPixel(4,red,green,blue);
					setPixel(5,red,green,blue);
				}

				function setMinuutVijf(red,green,blue) {
					setPixel(7,red,green,blue);
					setPixel(8,red,green,blue);
					setPixel(9,red,green,blue);
					setPixel(10,red,green,blue);
				}

				function setMinuutTien(red,green,blue) {
					setPixel(11,red,green,blue);
					setPixel(12,red,green,blue);
					setPixel(13,red,green,blue);
					setPixel(14,red,green,blue);
				}

				function setVoor1(red,green,blue) {
					setPixel(18,red,green,blue);
					setPixel(19,red,green,blue);
					setPixel(20,red,green,blue);
					setPixel(21,red,green,blue);
				}

				function setOver1(red,green,blue) {
					setPixel(22,red,green,blue);
					setPixel(23,red,green,blue);
					setPixel(24,red,green,blue);
					setPixel(25,red,green,blue);
				}

				function setKwart(red,green,blue) {
					setPixel(28,red,green,blue);
					setPixel(29,red,green,blue);
					setPixel(30,red,green,blue);
					setPixel(31,red,green,blue);
					setPixel(32,red,green,blue);
				}
				
				function setHalf(red,green,blue) {
					setPixel(33,red,green,blue);
					setPixel(34,red,green,blue);
					setPixel(35,red,green,blue);
					setPixel(36,red,green,blue);
				}

				function setOver2(red,green,blue) {
                                        setPixel(40,red,green,blue);
                                        setPixel(41,red,green,blue);
                                        setPixel(42,red,green,blue);
                                        setPixel(43,red,green,blue);
                                }

                                function setVoor2(red,green,blue) {
                                        setPixel(44,red,green,blue);
                                        setPixel(45,red,green,blue);
                                        setPixel(46,red,green,blue);
                                        setPixel(47,red,green,blue);
                                }

				function setUurEen(red,green,blue) {
                                        setPixel(51,red,green,blue);
                                        setPixel(52,red,green,blue);
                                        setPixel(53,red,green,blue);
                                }

				function setUurTwee(red,green,blue) {
                                        setPixel(55,red,green,blue);
                                        setPixel(56,red,green,blue);
                                        setPixel(57,red,green,blue);
                                        setPixel(58,red,green,blue);
                                }
				
				function setUurDrie(red,green,blue) {
                                        setPixel(62,red,green,blue);
                                        setPixel(63,red,green,blue);
                                        setPixel(64,red,green,blue);
                                        setPixel(65,red,green,blue);
                                }

				function setUurVier(red,green,blue) {
                                        setPixel(66,red,green,blue);
                                        setPixel(67,red,green,blue);
                                        setPixel(68,red,green,blue);
                                        setPixel(69,red,green,blue);
                                }

				function setUurVijf(red,green,blue) {
                                        setPixel(70,red,green,blue);
                                        setPixel(71,red,green,blue);
                                        setPixel(72,red,green,blue);
                                        setPixel(73,red,green,blue);
                                }

				function setUurZes(red,green,blue) {
                                        setPixel(74,red,green,blue);
                                        setPixel(75,red,green,blue);
                                        setPixel(76,red,green,blue);
                                }

				function setUurZeven(red,green,blue) {
                                        setPixel(77,red,green,blue);
                                        setPixel(78,red,green,blue);
                                        setPixel(79,red,green,blue);
                                        setPixel(80,red,green,blue);
                                        setPixel(81,red,green,blue);
                                }

				function setUurNegen(red,green,blue) {
                                        setPixel(83,red,green,blue);
                                        setPixel(84,red,green,blue);
                                        setPixel(85,red,green,blue);
                                        setPixel(86,red,green,blue);
                                        setPixel(87,red,green,blue);
                                }
				
				function setUurAcht(red,green,blue) {
                                        setPixel(88,red,green,blue);
                                        setPixel(89,red,green,blue);
                                        setPixel(90,red,green,blue);
                                        setPixel(91,red,green,blue);
                                }

				function setUurTien(red,green,blue) {
                                        setPixel(92,red,green,blue);
                                        setPixel(93,red,green,blue);
                                        setPixel(94,red,green,blue);
                                        setPixel(95,red,green,blue);
                                }

				function setUurElf(red,green,blue) {
                                        setPixel(96,red,green,blue);
                                        setPixel(97,red,green,blue);
                                        setPixel(98,red,green,blue);
                                }

				function setUurTwaalf(red,green,blue) {
                                        setPixel(99,red,green,blue);
                                        setPixel(100,red,green,blue);
                                        setPixel(101,red,green,blue);
                                        setPixel(102,red,green,blue);
                                        setPixel(103,red,green,blue);
                                        setPixel(104,red,green,blue);
                                }

				function setUur(red,green,blue) {
					setPixel(107,red,green,blue);
					setPixel(108,red,green,blue);
					setPixel(109,red,green,blue);
				}

				function setPixel(pixel,red,green,blue) {
					document.getElementById("LED-"+pixel).style.color="rgb("+red+","+green+","+blue+")";
				}
			</script>
	</body>
</html>
	
