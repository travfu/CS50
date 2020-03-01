function validate() {
    // clear previous pyramid and error message
    document.getElementById("mario").innerHTML="";
    document.getElementById("error").innerHTML="";
    
    // generate random placeholder number
    document.getElementById("inputHeight").setAttribute("placeholder", Math.floor(Math.random() * 23) + 1);
    
    var input = document.getElementById("inputHeight").value;
    // execute mario() if valid input
    if(input > 0 && input <= 23) {


        mario();
    }
    else{
        // clear input field and refocus input field if validation fails
        document.getElementById("inputHeight").value="";
        document.getElementById("inputHeight").focus();
        
        document.getElementById("error").innerHTML="Please enter a number between 0-23";
        return false;
    }
}

function mario()
{
    // get user input
    var h = document.getElementById("inputHeight").value;
    var w = (2*h) + 2;

    // generate a table
    var newTable = document.createElement("table");
    newTable.setAttribute("id", "pyramid");
    document.getElementById("mario").appendChild(newTable);

    // generate number of rows based on pyramid height (h)
    for (i = 0; i < h; i++)
    {
        var newRow = document.createElement("tr");
        newRow.setAttribute("id", "row" + i)
        document.getElementById("pyramid").appendChild(newRow);
    
        // generate columns
        for (let j = 0; j < w; j++)
        {
            var newCol = document.createElement("td");
            newCol.setAttribute("id", "col" + j);
            document.getElementById("row" + i).appendChild(newCol);
        }
    }
          
    // fill tables to generate pyramid row-by-row
    for (i = 0; i < h; i++)
    {
        // generate pyramid from bottom to top
        for(j = 0; j < h-i; j++)
        {
            // if height = 3
            // --#--#--
            // -##--##-
            // ###--###
            
            var offsetL = j + i;                  // in each row, shift to 1 column right 
            var offsetR = j + h*1 + 2;            // in each row, start right pyramid from
            
            var PyrBlockL = document.createElement("img");
            PyrBlockL.setAttribute("src", "Block.jpg"); 

            var PyrBlockR = document.createElement("img");
            PyrBlockR.setAttribute("src", "Block.jpg");

            // generate left pyramid
            document.getElementsByTagName("tr")[h-i-1].getElementsByTagName("td")[offsetL].appendChild(PyrBlockL);
            //generate right pyramid
            document.getElementsByTagName("tr")[h-i-1].getElementsByTagName("td")[offsetR].appendChild(PyrBlockR);
        }
    }
}