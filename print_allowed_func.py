# import 

with open("allowed_funcs.txt", 'r') as f:
    content = f.read()

# print(content) # for debug

funcs_list = [ func.strip() for func in content.split(",")]
funcs_list.sort()
for func in funcs_list:
    print(func)
