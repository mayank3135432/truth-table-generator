Instructions:  
Generates truth table for given expression
run the .sh file inside this directory  
./boolean_table_generator.sh  

enter your bool expression in stdin  

Boolean symbols used:  

^ is AND  

v is OR  

\> is implication (conditional)  

~ is negation  

= is equivalence (biconditional)

booltable(Aug 2023 -): This was created over a span of a few months in mid 2023. It takes in a boolean expression in 2,3 or 4 variables as input and prints out it's Truth Table. I was taking Discrete Mathematics in university at that time and this program made it absolutely trivial for me to verify my truth tables and check up valid rules of inferences.
However I do not considier this complete as I am yet make a parser that checks if passed in string is a valid boolean expression or not.
