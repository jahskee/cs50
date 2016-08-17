<?php
 
    // configuration
    require("../includes/config.php"); 
 
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell_form.php", ["title" => "Sell"]);
    }
 
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $rows = cs50::query("SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["user_id"], strtoupper($_POST["symbol"]));
 
        if (count($rows) == 0)
        {
            apologize("You do not currently own any shares of {$_POST["symbol"]}");
        }
 
        $row = $rows[0];
        
        if($_POST["shares"] < 1){
            apologize("You cannot sless shares less than quantity of 1");
        }
 
        if ($row["shares"] < $_POST["shares"])
        {
            apologize("You do not own {$_POST["shares"]} of {$_POST["symbol"]}. Please enter a lower quantity");
        }
 
        if ($row["shares"] == $_POST["shares"]) 
        {
            CS50::query("DELETE FROM portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["user_id"], $_POST["symbol"]);
        }
        else
        {
            CS50::query("UPDATE portfolio SET shares = ? WHERE user_id = ? AND symbol = ?", $row["shares"] - $_POST["shares"], $_SESSION["user_id"], $_POST["symbol"]);
        }
 
        $stock = lookup($_POST["symbol"]);
 
        CS50::query("UPDATE users SET cash = cash + ? WHERE username = ?", $_POST["shares"]*$stock["price"], $_SESSION["username"]);
 
        CS50::query("INSERT INTO history (id, transaction, timestamp, symbol, shares, price) VALUES (?, ?, ?, ?, ?, ?)", $_SESSION["user_id"], "SELL", date('Y-m-d h:i:s'), strtoupper($_POST["symbol"]), $_POST["shares"], $stock["price"]);
 
        redirect("/");
 
    }
 
?>