def get_key_from_dict(dict):
    return list(dict)[0]

def get_firstValue_from_dict(dict):
    return dict[get_key_from_dict(dict)]

def get_dict_from_arguments(arg1, arg2):
    formateDict = {}
    formateDict.update({arg1 : arg2})

    return formateDict
