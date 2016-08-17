<?php
     // configuration
    require("../includes/config.php"); 
 
    $transactions = CS50::query("SELECT * FROM history WHERE id = ?", $_SESSION["user_id"]);
    render("history_info.php", ["transactions" => $transactions, "title" => "History"]);
 
?>
