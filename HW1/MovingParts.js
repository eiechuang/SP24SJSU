function PW() {
    // Hardcoded password
    var password = "frankbutt"; // Replace with your desired password

    // Get the value of the entered password
    var enteredPassword = document.getElementById("validate").value;

    // Check if the entered password matches the hardcoded password
    if (enteredPassword === password) {
        // If correct, redirect to the referenced HTML page
        window.location.href = "transcript hw1.html"; // Redirects to the page
    } else {
        // If incorrect, display an alert
        alert("Incorrect password. Please try again.");
    }
}
    function navigateToPage() {
        var selectedValue = document.getElementById("projectDropdown").value;
        if (selectedValue === "waterCalculator") {
            window.location.href = "WaterCalc.html"; 
        } else if (selectedValue === "frontEndjava") {
            window.location.href = "frontEndjava.html"; 
        }
    }
