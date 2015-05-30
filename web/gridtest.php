<table>
<tr><?php
$gridOffset = 2;
$pixelsPerRow = 11;
$totalPixels = 121;

for($row=0;$row< ($totalPixels/$pixelsPerRow);$row++) {
	echo "<tr>";
	if($row%2 == 0) {
		$from = $row*$pixelsPerRow + $gridOffset;
		$to = $from+$pixelsPerRow - 1;
		for($col = $from; $col <= $to; $col++) {
			echo "<td> " . $col . " </td>";
		}
	} else {
		$from = $row*$pixelsPerRow + $gridOffset;
                $to = $from+$pixelsPerRow - 1;
                for($col = $to; $col >= $from; $col--) {
                        echo "<td> " . $col . " </td>";
                }
	}
	echo "</tr>";
	/*if(($i/$ledsPerRow)%2) {
		$lednr = 11 - ($i % $ledsPerRow);
		echo "<td>" . ($i+$gridOffset) . "(" . $lednr . ")</td>";
	} else {
		echo "<td>" . ($i+$gridOffset) . "</td>";
	}
	if($i>0 && ($i+1)%$ledsPerRow == 0) {
		echo "</tr><tr>";
	}*/
}

?>
</tr>
</table>
