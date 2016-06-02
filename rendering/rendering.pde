PImage img; 
void setup(){
  size(1183,608);
  img = loadImage("../erb1.png"); //loading the image of the floorplan 
 }
 
 int i= 0; 
 public class agent_class {
   String[] agentnames = new String[250];   //creating names such as agent0, agent1, agent2, .... to agent250 
   public String[] setnames(){
   for (int j = 0; j<250; j++){
     String name = "agent"+ String.valueOf(j); 
     agentnames[j]=name; 
   } 
   return agentnames; 
 }
 } 
      
agent_class all_agents= new agent_class(); //creating new object all_agent 
String[] s = all_agents.setnames();  // saving the agent names in the string[] s 


 void draw(){
  background(0); 
  image(img, 0, 0);
  i++;
  for (int agent =0; agent <250; agent++){  
     Table table = loadTable (s[agent]+ ".csv"); //importing the csv files 
     if (i<table.getRowCount()-1){
       TableRow row = table.getRow(i); //taking single row at a time 
       int x = row.getInt(0);
       int y = row.getInt(1);
       ellipse(x,y,5,5);  //circle of 10 pixels diameter 
     }
     
  }   
 }
