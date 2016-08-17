 <?php
    // configuration
	require("../includes/config.php");
 
    // if user reached page via GET (as by clicking a link or via redirect)
	if ($_SERVER["REQUEST_METHOD"] == "GET") {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
 
    // else if user reached page via POST (as by submitting a form via POST)
	else if ($_SERVER["REQUEST_METHOD"] == "POST") {
		if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide a password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        else if ($_POST["confirmation"] != $_POST["password"])
        {
        	apologize("Password and confirmation do not match");
        	redirect("/"); 
        	
        }
 
        // query database for user
        $success = CS50::query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
 
        if ($success === false)
        {
        	apologize("Account creation failed");
        } 
        else {
        	$rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
	    	$id = $rows[0]["id"];
    
	        // remember that user's now logged in by storing user's ID in session
	        $_SESSION["user_id"] = $id;
	      
            $user = CS50::query("SELECT username FROM users where id=? limit 1", $id);
            
            $_SESSION["username"]="";
             if (count($user) == 1){
                $_SESSION["username"] = $user[0]["username"];
             }
             
             
            
            //$_SESSION["username"] = "jahskee";
	        redirect("/"); 
        }   	
 
        
	}
?>