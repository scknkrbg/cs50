<?php
	
	// configuration
	require("../includes/config.php");

	// if user reached page via GET (a by clicking or via redirect)
	if($_SERVER["REQUEST_METHOD"] == "GET")
	{
		// else render form
		render("register_form.php", ["title" => "Register"]);
	} 
	
	else if ($_SERVER["REQUEST_METHOD"] == "POST")
	{
		if(empty($_POST["username"]))  //or empty($_POST["password"]) or ($_POST["password"] != $_POST["confirmation"]))
		{
			apologize("We think you do not want to be called user62124! Let's choose a cool username: feristah?");
		}
		else if(empty($_POST["password"]))
		{
			apologize("We appreciate that you use the same password everywhere!");
		}
		else if($_POST["password"] != $_POST["confirmation"])
		{
			apologize("When you confirm your password, a butterfly dies somewhere in Serengeti!");
		}
		else
		{
			$username_check = CS50::query("SELECT * FROM users WHERE username = ?", $_POST["username"]);
			// $username_check[0]["username"] == $_POST["username"]
			if($username_check[0]["username"] == $_POST["username"])
			{
				apologize("It is already being taken!");
				// render("apology.php", ["title" => "Register", "optional" => $_POST["username"], "message" => " is someone else's love!"]);
			}
			else
			{
				$insert_user = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", 
				$_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));	
				$last = CS50 :: query("SELECT LAST_INSERT_ID() AS id");
				$_SESSION["id"] = $last[0]["id"];
				redirect("index.php");
			}
		}
	}
?>

