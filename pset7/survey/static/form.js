function validate(event) {
    if (document.getElementById("name").value == "") {
        event.preventDefault();
        event.stopPropagation();
        alert("Please enter your name")
    } else if (document.getElementById("inputCharacters").value == "invalid") {
        event.preventDefault();
        event.stopPropagation();
        alert("Please select your favourite Avenger")
    } else {
        return
    }
}