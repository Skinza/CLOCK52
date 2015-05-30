<!DOCTYPE html>
<html>
	<head>
		<title>Clock 52 Sim test 3</title>
		<link href='http://fonts.googleapis.com/css?family=Source+Code+Pro' rel='stylesheet' type='text/css'>
		<link href='styles/clockSim3.css' rel='stylesheet' type='text/css'>
		<script type="text/javascript" src="scripts/clockSim3.js" ></script>
	</head>
	<body onload="bootstrap()">
		<?php
			error_reporting(-1);
			ini_set('display_errors', 'On');
			
			
			$letters = 	"HETKISAVIJF" .
					"ROOVZTBNEIT" .
					"OVERMEKWART" .
					"REVOWPSFLAH" .
					"VOORTHGEENS" .
					"EIRDCVPEEWT" .
					"VIERVIJFZES" .
					"NEGENONEVEZ" .
					"ACHTTIENELF" .
					"RUUFBFLAAWT" .
					"1234567890X";
			
			$pixelGridOffset = 2;
			$pixelsPerRow = 11;
			$pixelsInGrid = 121;
			?>
			<div id="clock52">
				<div id="LED-1" class="minuutIndicator LED">&#149;</div>
				<div id="LED-0" class="minuutIndicator LED">&#149;</div>
				<div id="LED-123" class="minuutIndicator LED">&#149;</div>
				<div id="LED-124" class="minuutIndicator LED">&#149;</div>
				<table id="clock52grid">
					<?php
						for($row=0;$row< ($pixelsInGrid/$pixelsPerRow);$row++) {
							echo "<tr>";
							if($row%2 == 0) {
								$from = $row*$pixelsPerRow + $pixelGridOffset;
								$to = $from+$pixelsPerRow - 1;
								for($col = $from; $col <= $to; $col++) {
									echo "<td class=\"clock52letter LED\" id=\"LED-".($col)."\">" . $letters[$col-$pixelGridOffset] . "</td>";
								}
							} else {
								$from = $row*$pixelsPerRow + $pixelGridOffset;
								$to = $from+$pixelsPerRow - 1;
								for($col = $to; $col >= $from; $col--) {
									echo "<td class=\"clock52letter LED\" id=\"LED-".($col)."\">" . $letters[$col-$pixelGridOffset] . " </td>";
								}
							}
							echo "</tr>";
						}
					?>
				</table>
			</div>
			Uur: <input type="text" disabled="disabled" id="uurTxt" /><input type="button" value="+" disabled="disabled" id="uurPlus" onClick="uurPlus()" /><input type="button" value="-" disabled="disabled" id="uurMin" onClick="uurMin()" /><br />
			Minuut: <input type="text" disabled="disabled" id="minuutTxt" /><input type="button" value="+" disabled="disabled" id="minuutPlus" onClick="minuutPlus()" /><input type="button" value="-" disabled="disabled" id="minuutMin" onClick="minuutMin()" /><br />
			<input type="button" id="toggleManual" value="Handmatig" onclick="toggleManual()" /> 
	</body>
</html>
	
