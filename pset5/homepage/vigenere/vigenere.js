const letters = /^[A-Za-z]+$/;    // regex pattern for [English] alphabetical letters
const alphabetCount = 26;         // number of letters in alphabet
const upper = 65;                 // value to reduce A-Z letters in ASCII to 0-25
const lower = 97;                 // value to reduce a-z letters in ASCII to 0-25


function validate() {
    // clear previous
    document.getElementById("error").innerHTML="";
    document.getElementById("vigenere").innerHTML="";
    
    // check if plaintext has text
    if(document.getElementById("inputText").value=="" || document.getElementById("inputKey").value=="" )
    {
        document.getElementById("error").innerHTML="Oops: Please enter plaintext and key";
        return false;
    }
    
    // if key is alphabetical...
    if(document.getElementById("inputKey").value.match(letters)) 
    {
        vigenere();
    }
    // if key contains non-alphabetical...
    else 
    {
        document.getElementById("error").innerHTML="Oops: Key can only accept [English] alphabetical letters. Spaces are not accepted."
        return false;
    }
}    

function vigenere()
{
    // convert key to indexed number and store in an array
    var key = [];
    key.length = document.getElementById("inputKey").value.length;          

    for (i = 0; i < key.length; i++)
    {
        key[i] = document.getElementById("inputKey").value[i];

        if(key[i] == key[i].toUpperCase())
        {
            key[i] = document.getElementById("inputKey").value.charCodeAt(i) - upper;
        }
        else if(key[i] == key[i].toLowerCase())
        {
            key[i] = document.getElementById("inputKey").value.charCodeAt(i) - lower;
        }
    }

    // get plaintext and apply vigenere encryption
    var text = []
    text.length = document.getElementById("inputText").value.length;

    for (i = 0, j = 0; i < document.getElementById("inputText").value.length; i++)
    {
        text[i] = document.getElementById("inputText").value[i]

        if(text[i].match(letters))
        {
            if(text[i] === text[i].toUpperCase())
            {
                // do this if uppercase
                text[i] = ( document.getElementById("inputText").value.charCodeAt(i) + key[j % key.length] - upper ) % alphabetCount + upper;
                text[i] = String.fromCharCode(text[i]);
            }
            else if (text[i] === text[i].toLowerCase())
            {
                // do this if lowercase
                text[i] = ( document.getElementById("inputText").value.charCodeAt(i) + key[j % key.length] - lower ) % alphabetCount + lower;
                text[i] = String.fromCharCode(text[i]);
            }
            // increment counter for key[j] only if it has been used to modify a plaintxt letter
            j++;
        }
    }

    // display ciphertext
    document.getElementById("vigenere").innerHTML=text.join("");
}