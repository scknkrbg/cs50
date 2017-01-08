<?php
	
	// configuration
	require("../includes/config.php");

	// if user reached page via GET (a by clicking or via redirect)
	if($_SERVER["REQUEST_METHOD"] == "GET")
	{
		// else render form
		render("buy_form.php", ["title" => "Buy"]);
	} 
	
	else if ($_SERVER["REQUEST_METHOD"] == "POST")
	{
		if(empty($_POST["symbol"]))  //or empty($_POST["password"]) or ($_POST["password"] != $_POST["confirmation"]))
		{
			apologize("Empty symbol means buy anything?");
		}
		else if(empty($_POST["shares"]))
		{
			apologize("Empty share number means buy all of them?");
		}
		else
		{
		    // looking up current share price
			$symbol_current = lookup($_POST["symbol"]);
			// looking up the share in the portfolio table
			$symbol_check = CS50::query("SELECT * FROM portfolio WHERE user_id = ? and symbol = ?", $_SESSION["id"], $_POST["symbol"]);
			$cash_check = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
			
			// symbol is empty or invalid
			if(empty($_POST["symbol"]) or $symbol_current === false)
			{
			    apologize("Enter a valid share symbol!");
			}
			// share number is negative or empty
			if(empty($_POST["shares"]) or preg_match("/^\d+$/", $_POST["shares"]) == false)
			{
			    apologize("Enter a valid number of shares to buy!");
			}
			// insufficient money balance
			else if($cash_check[0]["cash"] < $_POST["shares"] * $symbol_current["price"])
			{
			    apologize("You do not have sufficent money in your balance!");
			}
			else
			{
			    $time = CS50::query("SELECT NOW() as time");
				$insert_portfolio = CS50::query("INSERT INTO portfolio (user_id, symbol, bought_price,  bought_quantity, active_quantity, 
				date_created, status)
				VALUES (?, ?, ?, ?, ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], 
				$symbol_current["price"], $_POST["shares"], $_POST["shares"],
				$time[0]["time"], 1);
				
				
				$update_cash = CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", 
				$_POST["shares"] * $symbol_current["price"], $_SESSION["id"]);
				
				
			}

		redirect("index.php");
		}
    }
?>