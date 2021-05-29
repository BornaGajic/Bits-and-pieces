window.onload = function(){    

    let inputScreen = document.getElementById("inputScreen");
    let outputScreen = document.getElementById("outputScreen");

    let brIsHere = true;
    
    function numberClickHandler (e)
    {
        let number = e.target.innerText;

        if (inputScreen.innerText.length == 0)
        {
            inputScreen.parentElement.querySelector("br").remove();
            outputScreen.parentElement.querySelector("br").remove();

            brIsHere = false;
        }

        if (number == ".")
        {
            let charIndex = inputScreen.innerText.length - 1;

            if (charIndex == -1)
            {
                if (!brIsHere)
                {
                    outputScreen.parentElement.appendChild(document.createElement("br"));
                    inputScreen.parentElement.appendChild(document.createElement("br"));
        
                    brIsHere = true;
                }
                
                return;
            }
            else if (inputScreen.innerText[charIndex] == '.') return;

            while ("÷×+-".includes(inputScreen.innerText[charIndex]) == false)
            {
                if (inputScreen.innerText[charIndex--] == '.') return;
                if (charIndex == -1) break;
            }
        }

        inputScreen.innerText += number;
        outputScreen.innerText += number;

        let parsedInput = inputScreen.innerText.replaceAll("÷", "/").replaceAll("×", "*");

        outputScreen.innerText = eval(parsedInput);
    }

    function operationClickHandler (e)
    {
        let operation = e.target.innerText;

        if (operation == "C")
        {
            if (inputScreen.innerText.length > 0)
            {
                inputScreen.innerText = "";
                outputScreen.innerText = "";

                outputScreen.parentElement.appendChild(document.createElement("br"));
                inputScreen.parentElement.appendChild(document.createElement("br"));

                brIsHere = true;

                return;
            }

            return;
        }
        else
        {
            if (operation == "⌫" && inputScreen.innerText.length > 0)
            {
                inputScreen.innerText = inputScreen.innerText.slice(0, -1);
                outputScreen.innerText = inputScreen.innerText;

                if (inputScreen.innerText.length > 0 && "0123456789".includes(inputScreen.innerText.slice(-1))) 
                {
                    let parsedInput = inputScreen.innerText.replace("÷", "/").replace("×", "*");
                    outputScreen.innerText = eval(parsedInput);
                }
            }
            else if (inputScreen.innerText.length > 0)
            {
                if ("÷×".includes(inputScreen.innerText.slice(-1)) && operation == "-")
                    inputScreen.innerText += "-";
                else if ("-".includes(inputScreen.innerText.slice(-1)))
                {   
                    if ("0123456789".includes(inputScreen.innerText[inputScreen.innerText.length - 2])) 
                    {
                        inputScreen.innerText = inputScreen.innerText.slice(0, -1) + operation;
                    }
                    else
                        return;
                }
                else
                {
                    if ("÷×+-".includes(inputScreen.innerText.slice(-1)))
                        inputScreen.innerText = inputScreen.innerText.slice(0, -1) + operation;
                    else
                        inputScreen.innerText += operation;
                }
            }

            if (inputScreen.innerText.length == 0)
            {
                if (!brIsHere)
                {
                    outputScreen.parentElement.appendChild(document.createElement("br"));
                    inputScreen.parentElement.appendChild(document.createElement("br"));

                    brIsHere = true;
                }
            }
        }
    }

    function onEqClickHandler ()
    {
        inputScreen.innerText = outputScreen.innerText;
    }

    let operationsList = document.getElementsByClassName("op");
    let numbersList = document.getElementsByClassName("number");

    let eq = document.getElementById("eq");
    eq.onclick = onEqClickHandler;
    eq.style.cursor = "pointer";

    [].forEach.call(operationsList, function (op) { 
        op.onclick = operationClickHandler; 
        op.style.cursor = "pointer";
    });

    [].forEach.call(numbersList, function (num) { 
        num.onclick = numberClickHandler; 
        num.style.cursor = "pointer";
    });
};