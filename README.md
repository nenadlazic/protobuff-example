# protobuf-example
 This example demonstrates the usage of Protocol Buffers (protobuf) in C++ for serializing, deserializing, and printing structured data. Protocol Buffers are a mechanism developed by Google to efficiently serialize structured data for communication and storage.

## Usage
### Compile command:
`g++ -o protobuf-example main.cpp projectmanagement.pb.cc -lprotobuf -pthread`

### Run command:
`./protobuf-example`

### Output will be something like the following log:

```
############################ Before serialization ##############################
Project: Sample
URL: http://www.sample.com
Developers:
Developer 1:
  First name: ABC
  Last name: XYZ
  Email: abc.xyz@example.com
Developer 2:
  First name: DEF
  Last name: GHI
  Email: def.ghi@example.com
################################################################################

########################## Serialized Data (Hex) - write #######################
0a 06 53 61 6d 70 6c 65 12 15 68 74 74 70 3a 2f 2f 77 77 77 2e 73 61 6d 70 6c 65 2e 63 6f 6d 1a 1f 0a 03 41 42 43 12 03 58 59 5a 1a 13 61 62 63 2e 78 79 7a 40 65 78 61 6d 70 6c 65 2e 63 6f 6d 1a 1f 0a 03 44 45 46 12 03 47 48 49 1a 13 64 65 66 2e 67 68 69 40 65 78 61 6d 70 6c 65 2e 63 6f 6d 
################################################################################

######################### Serialized Data (Hex) - read ########################
0a 06 53 61 6d 70 6c 65 12 15 68 74 74 70 3a 2f 2f 77 77 77 2e 73 61 6d 70 6c 65 2e 63 6f 6d 1a 1f 0a 03 41 42 43 12 03 58 59 5a 1a 13 61 62 63 2e 78 79 7a 40 65 78 61 6d 70 6c 65 2e 63 6f 6d 1a 1f 0a 03 44 45 46 12 03 47 48 49 1a 13 64 65 66 2e 67 68 69 40 65 78 61 6d 70 6c 65 2e 63 6f 6d 
###############################################################################

######################### After deserialization ################################
Project: Sample
URL: http://www.sample.com
Developers:
Developer 1:
  First name: ABC
  Last name: XYZ
  Email: abc.xyz@example.com
Developer 2:
  First name: DEF
  Last name: GHI
  Email: def.ghi@example.com
################################################################################
```
