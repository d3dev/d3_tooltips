<?php
$count = 0;
$db = new PDO('sqlite:../items.db');
$id = $_POST['id'];
$price = $_POST['price'];
if (is_numeric($id) && is_numeric($price)) $count = $db->exec("UPDATE d3_custom SET sold=$price WHERE id=$id");
echo $count;
?>
