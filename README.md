# Json Editing (C++)
A program that showcases how to read and write json files in C++. The purpose of this project is to give a general idea of how [nlohmann's json](https://github.com/nlohmann/json) library works. The cpp file has two parts where we first show how to add an entry to the json file and the second part shows how to edit an existing entry.

**Reading and Writing a Json File**
-----------------------------------------
Example of how to read and write a json file. If you wish to open from a specific directory, replace ```sample.json``` with something like this ```D:\\Users\\Username\\Desktop\\sample.json```.
```
//Read Json File into a jsonObject
std::ifstream file;
file.open("sample.json");

nlohmann::json jsonObject;
if(file.is_open()){
  file >> jsonObject;
}

//Close the file
file.close();

//Creating json file
std::ofstream file2("sampleEdited.json");
std::cout << jsonObject.dump(2);
```

**Adding a New Entry to a Json File**
-----------------------------------------
Currently our sample.json file looks like this:
```
[
    {
      "id": 100,
      "sorc": "1.2.3.4",
      "dest": "5.4.3.2",
      "srvc": "tcp/22",
      "desc": "Data Center A"
    },
    {
      "id": 101,
      "sorc": "1.2.3.4",
      "dest": "5.4.3.2",
      "srvc": "tcp/80",
      "desc": "Data Center B"
    },
    {
      "id": 102,
      "sorc": "1.2.3.4",
      "dest": "5.4.3.2",
      "srvc": "tcp/443",
      "desc": "Data Center B"
    }
]
```
Let's say we want to add a new entry into it. To do so, we can find out how many entries there are (thus giving us their indexes) and then add a new entry at the next index. In the above json file, we can see that there are 3 entries. We can type in 3 for the index or we can use the json file's built in size function.
```
//Add a new entry at the 3rd index
int jsonSize = jsonObject.size();
jsonObject[jsonSize]["id"] = 103;
jsonObject[jsonSize]["sorc"] = "1.2.3.4";
jsonObject[jsonSize]["dest"] = "5.4.3.2";
jsonObject[jsonSize]["srvc"] = "tcp/5070";
jsonObject[jsonSize]["desc"] = "Data Center C";
```
Doing all this will give us this as a new entry:

```
{
    "desc": "Data Center C",
    "dest": "5.4.3.2",
    "id": 103,
    "sorc": "1.2.3.4",
    "srvc": "tcp/5070"
}
```
**Editing an Existing Entry in a Json File**
-----------------------------------------
Our second sample json file is slightly different compared to the first one. It has entries under a person's name, so working with it will be slightly different. The second sample json file can be seen below.

```
{
   "Joe":{
      "Age": 20,
      "Lap Time": "1:02",
      "Best Time": "0:55",
      "Days Participated": ["Monday", "Wednesday", "Thursday"]
   },
   "Marco":{
      "Age": 17,
      "Lap Time": "1:22",
      "Best Time": "1:09",
      "Days Participated": ["Monday", "Tuesday", "Friday"]
   }
}
```
Let's say we made multiple mistakes in Marco's entry and now we want to edit it. Editing the json file is very similar to what we did above. However, you may notice that this json file has an array in the "Days Participated". We can use the json's library built in array function to create a json array or we can use the push_back function to add a day to it. I am going to skip how to read the json file into a jsonobject because that was covered above and can also be seen in the source code.

```
//Editing a current entry
jsonObject["Marco"]["Age"] = 19;
jsonObject["Marco"]["Lap Time"] = "2:11";
jsonObject["Marco"]["Best Time"] = "1:32";

//Creating a json array and adding it to the json object
json json_array = {"Saturday", "Sunday"};
jsonObject2["Marco"]["Days Participated"] = json_array;
jsonObject2["Marco"]["Days Participated"].push_back("Tuesday");
```
The new edits will give us this result:
```
{
    "Joe": {
        "Age": 20,
        "Best Time": "0:55",
        "Days Participated": [
            "Monday",
            "Wednesday",
            "Thursday"
        ],
        "Lap Time": "1:02"
    },
    "Marco": {
        "Age": 19,
        "Best Time": "1:32",
        "Days Participated": [
            "Saturday",
            "Sunday",
            "Tuesday"
        ],
        "Lap Time": "2:11"
    }
}
```
**Iterating over Keys**
---------------------------------
Iterating over keys may be helpful to get values very quickly, but the problem is that not all json objects are composed of key-value pairs. So the following code may not always work.

```
for (auto itr = jsonObject2.begin(); itr != jsonObject2.end(); ++itr) {
  std::cout << "key: " << itr.key() << " value: " << itr.value() << "\n";
}
```
Running the code above will print out:

```
key: Joe value: {"Age":20,"Best Time":"0:55","Days Participated":["Monday","Wednesday","Thursday"],"Lap Time":"1:02"}
key: Marco value: {"Age":19,"Best Time":"1:32","Days Participated":["Saturday","Sunday","Tuesday"],"Lap Time":"2:11"}
```

Similarly, we can iterate over a json array.
```
for (auto arrayItr = jsonObject2["Marco"].begin();
	arrayItr != jsonObject2["Marco"].end();
	++arrayItr) {
	std::cout << *arrayItr << " ";
}
```
Unlike keys, arrayItr points to values since the keys are simply indices. If we iterate over Marco's entry, we get:
```
19 "1:32" ["Saturday","Sunday","Tuesday"] "2:11"
```
