<?php
 
    // configuration
    require("../includes/config.php"); 
 
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }
 
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
 
        if ($stock === false)
        {
            apologize("The stock entered could not be found");
        }
 
        if($_POST["shares"] < 1){
            apologize("You cannot buy shares less than quantity of 1");
        }
 
 
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["user_id"])[0]["cash"];
       
        $buy_amount =  $_POST["shares"] * $stock["price"];
        if ($cash < $buy_amount)
        {
            apologize("You do not have enough money to make this purchase");
        }
        
 
 
        CS50::query("UPDATE users SET cash = cash - ? WHERE username = ?", $buy_amount, $_SESSION["username"]);
 
        CS50::query("INSERT INTO portfolio (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares+VALUES(shares)", $_SESSION["user_id"], strtoupper($_POST["symbol"]), $_POST["shares"]);
        
        CS50::query("INSERT INTO history (id, transaction, timestamp, symbol, shares, price) VALUES (?, ?, ?, ?, ?, ?)", $_SESSION["user_id"], "BUY", date('Y-m-d h:i:s'), strtoupper($_POST["symbol"]), $_POST["shares"], $stock["price"]);
        
        redirect("/");
    }
 
?>