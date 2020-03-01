function cash() {
            
    // reset output and error messages
    document.getElementById("displayQuarter").innerHTML="";
    document.getElementById("displayDime").innerHTML="";
    document.getElementById("displayNickel").innerHTML="";
    document.getElementById("displayPenny").innerHTML="";
    document.getElementById("error").innerHTML="";
    
    // get input        
    change = parseFloat(document.getElementById("inputChange").value);

    // validate number
    if(change <= 0 || change != parseFloat(change.toFixed(2)))
    {
        document.getElementById("error").innerHTML="Oops. Please enter a valid dollar value";
        return false;
    }

    // convert dollars to cents
    change = Math.trunc(change * 100);

    // quarters
    quarter = Math.floor(change / 25);
    change -= quarter * 25;

    // dimes
    dime = Math.floor(change / 10);
    change -= dime * 10;

    // nickel
    nickel = Math.floor(change / 5);
    change -= nickel * 5;
    
    // pennies
    penny = change;

    // display values on screen
    document.getElementById("displayQuarter").innerHTML= quarter;
    document.getElementById("displayDime").innerHTML= dime;
    document.getElementById("displayNickel").innerHTML= nickel;
    document.getElementById("displayPenny").innerHTML= penny;

}