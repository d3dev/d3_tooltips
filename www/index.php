<?php
$db = new PDO('sqlite:../items.db');
$col = 0;
$sth = $db->query("select c.id, c.owner, c.sold, t.* from d3_custom c JOIN d3_tooltips t ON c.id=t.id");
$sth->setFetchMode(PDO::FETCH_ASSOC);
$data = $sth->fetchAll();
?>
<!DOCTYPE html>
<html>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<style type="text/css" title="currentStyle">
    @import "DataTables/media/css/demo_table.css";
    @import "ColVis/media/css/ColVis.css";
    @import "ColReorder/media/css/ColReorder.css";
    .sell
    {
      color: #999;
      width: 55px;
    }
</style>
<script type="text/javascript" charset="utf-8" src="DataTables/media/js/jquery.js"></script>
<script type="text/javascript" charset="utf-8" src="DataTables/media/js/jquery.dataTables.js"></script>
<script type="text/javascript" charset="utf-8" src="ColVis/media/js/ColVis.js"></script>
<script type="text/javascript" charset="utf-8" src="ColReorder/media/js/ColReorder.js"></script>
<script type="text/javascript" charset="utf-8">
function clear()
{
 this.value="";
}
$(document).ready( function () {
    var oTable = $('#table_id').dataTable({
		"sDom": 'RC<"clear">lfrtip',
		"aoColumnDefs": [
			{ "bVisible": false, "aTargets": [ 0 ] }
		],
		"bSortCellsTop": true
	});

	$("thead input").keyup( function () {
		/* Filter on the column (the index) of this element */
		oTable.fnFilter( this.value, this.name );
	} );
	
	/*
	 * Support functions to provide a little bit of 'user friendlyness' to the textboxes
	 */
	$("thead input").each( function (i) {
		this.initVal = this.value;
	} );
	
	$("thead input").focus( function () {
		if ( this.className == "search_init" )
		{
			this.className = "";
			this.value = "";
		}
	} );
	
	$("thead input").blur( function (i) {
		if ( this.value == "" )
		{
			this.className = "search_init";
			this.value = this.initVal;
		}
	} );

	$("#table_id").on("focus", ".sell", function() { this.value=""; });
	$("#table_id").on("keyup", ".sell", function(e) {
		if (e.which == 13)
		{
			var price = parseInt(this.value) || 0;
			var p = $(this).parent();
			if (price != 0)
			{
				$.post( 'sell.php', { id: this.id, price: price },
				function( data ) {
					if (data == "1")
					{
						p.empty();
						p.append(price);
					}
				});
			}
		}
	});


} );
</script>

<?php
function slug($str)
{
 $r = '';
 $len = strlen($str);
 $state = 0;
 $cnt = 0;
 for($i = 0; $i < $len; $i++)
 {
  switch($state)
  {
   case 0: //text
    if($str[$i] == '{') $state = 1;
    else if($str[$i] == "\n") $r .= '<br/>';
    else $r .= $str[$i];
    break;
   case 1: //style
    if($str[$i] == '}') $state = 0;
    else if($str[$i] == 'c' || $str[$i] == 'C') $state = 2;
    else if($str[$i] == '/') $state = 5;
    break;
   case 2: //color
    if($str[$i] == '}') $state = 0;
    else if($str[$i] == '_') $state = 3;
    else if($str[$i] == ':') $state = 4;
    else $state = 1;
    break;
   case 3: //color name
    $state = 0;
    $start = $i;
    while($i < $len && $str[$i] != '}') ++$i;
    $r .= "<span style='color: ".substr($str, $start, $i-$start)."'>";
    break;
   case 4: //color num
    if($i + 8 < $len && $str[$i+8] == '}')
    {
     $state = 0;
     $cnt = 1;
     $r .= "<span style='color: #".substr($str, $i+2, 6)."'>";
     $i += 8;
    }
    else $state = 2;
    break;
   case 5: //end style
    if($str[$i] == 'c' || $str[$i] == 'C') $state = 6;
    else $state = 2;
    break;
   case 6: //end style
    if($str[$i] == '}') $state = 0;
    else $state = 2;
    $r .= '</span>';
    break;
   default:
    break;
  }
 }
 return $r;
}


echo '<table id="table_id" class="display"><thead><tr>';
foreach($data[0] as $k => $v)
{
 echo "<th>$k</th>";
}
echo '</tr><tr>';
foreach($data[0] as $k => $v)
{
 echo "<th><input type='text' name='".$col++."' value='Filter...' class='search_init'/></th>";
}
echo '</tr></thead><tbody>';

foreach($data as $row)
{
 echo '<tr>';
 foreach($row as $k => $v)
 {
  if ($k == 'sold' && $v == '0') echo "<td><input type='text' class='sell' value='Sell this' id='".$row['id']."' onFocus='clear()' /></td>";
  else echo '<td>'.slug($v).'</td>';
 }
 echo '</tr>';
}
echo '</tbody></table>';
?>
</html>
