<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (a by clicking or via redirect)
	if($_SERVER["REQUEST_METHOD"] == "GET")
	{
		// else render form
		render("quote_form.php", ["title" => "Quote"]);
	} 
    else if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(empty($_POST["quote"]))
        {
            apologize("Empty symbol implies bad luck! Please try again!");
        }
        else
        {
            $stock = lookup($_POST["quote"]);
            if(empty($stock["name"]))
            {
                apologize("Cannot be found! Enter a valid symbol!");
            }
            render("quote_display.php", ["price" => $stock["price"], "name" => $stock["name"], "symbol" => $stock["symbol"]]);
        }
        
    }
    


?>