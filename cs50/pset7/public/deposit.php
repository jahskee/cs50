<?php
 
    // configuration
    require("../includes/config.php"); 
 
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("deposit_form.php", ["title" => "Deposit"]);
    }
 
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
 
 
        if($_POST["deposit"] < 1){
            apologize("You cannot enter deposit less than $1.00");
            exit; 
        }
        
        
 
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["deposit"], $_SESSION["user_id"]);
        CS50::query("INSERT INTO history (id, transaction, timestamp, symbol, shares, price) VALUES (?, ?, ?, ?, ?, ?)", $_SESSION["user_id"], "DEPOSIT", date('Y-m-d h:i:s'), "CASH", 1 , $_POST["deposit"]);
        redirect("/");
        
    }
 
?>