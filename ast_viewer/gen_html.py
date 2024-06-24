import re

def parse_ast_string(s):
    # Remove surrounding whitespaces and split by spaces while keeping strings in quotes
    tokens = re.findall(r'\(|\)|\w+|\".*?\"', s.strip())

    def parse(tokens):
        if not tokens:
            return None
        token = tokens.pop(0)
        if token == '(':
            lst = []
            while tokens[0] != ')':
                lst.append(parse(tokens))
            tokens.pop(0)  # Remove ')'
            return tuple(lst)
        elif token == ')':
            return None
        elif token.startswith('"') and token.endswith('"'):
            return token[1:-1]
        elif token.isdigit():
            return int(token)
        else:
            return token

    return parse(tokens)

# conver to a map, the first element is the key and the rest are values
def to_map(ast):
    if isinstance(ast, str):
        return ast
    if not isinstance(ast, tuple):
        return ast
    
    if len(ast) == 0:
        return {}
    key = ast[0]
    values = ast[1:]
    return {key: [to_map(v) for v in values]}

if __name__ == '__main__':
  # ast_string from argv 0 
  import sys
  file_name = sys.argv[1]
  ast_string=""
  with open(file_name) as f:
    ast_string = f.read()
  # Parse the AST string
  ast_tuple = parse_ast_string(ast_string)

  # convert it into json
  import json
  ast_json = json.dumps(to_map(ast_tuple))

  # html template
  template = """
  <!DOCTYPE html>
  <html lang="en">

  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>JSON Viewer</title>
      <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
      <script src="ast_viewer/json-viewer.js"></script>
      <link rel="stylesheet" href="ast_viewer/style.css">
  </head>

  <body>
      <pre id="json-renderer"></pre>

      <script>
          $(document).ready(function () {{
              const testJson =`{0}`
              // Initialize the JSON Viewer
              new JsonViewer({{
                  container: $('#json-renderer')[0],
                  data: testJson,
                  theme: 'light',
                  expand: false
              }});
          }});
      </script>
  </body>
  </html>
  """

  string = template.format(ast_json)
  print(string)
