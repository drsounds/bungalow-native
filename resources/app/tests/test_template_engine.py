import sys
import unittest
from pathlib import Path

APP_DIR = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(APP_DIR))

import index
from template_engine import TemplateError, render_string, render_template


class TemplateEngineTests(unittest.TestCase):
    def test_interpolation_and_nested_context(self):
        rendered = render_string(
            '<text>${model.title}: ${data.count}</text>',
            {'model': {'title': 'Overview'}, 'data': {'count': 3}},
        )
        self.assertIn('<text>Overview: 3</text>', rendered)

    def test_count_loop_and_lua_control_flow(self):
        rendered = render_string(
            '<list>\n% for i,3 do\n<item>${i}</item>\n% end\n</list>'
        )
        self.assertIn('<item>1</item>', rendered)
        self.assertIn('<item>2</item>', rendered)
        self.assertIn('<item>3</item>', rendered)

    def test_request_bindings_and_context_are_available(self):
        rendered = render_string(
            '<text>${method} ${uri} ${action} ${data.name} ${now}</text>',
            {
                'method': 'POST',
                'uri': '/start',
                'action': 'refresh',
                'data': {'name': 'Ada'},
                'now': '12:30',
            },
        )
        self.assertIn('<text>POST /start refresh Ada 12:30</text>', rendered)

    def test_template_literals_escape_lua_string_delimiters(self):
        rendered = render_string('<text title="a \\"quote\\"">ok</text>')
        self.assertIn('<text title="a \\"quote\\"">ok</text>', rendered)

    def test_lua_errors_are_reported_as_template_errors(self):
        with self.assertRaisesRegex(TemplateError, 'Lua template execution failed'):
            render_string('<text>${missing.value}</text>', name='broken.xml')

    def test_current_views_render_through_lua(self):
        rendered = render_template('start.xml', now='fixed time')
        self.assertIn('Current time is fixed time', rendered)
        self.assertNotIn('${now}', rendered)

    def test_view_path_cannot_escape_template_directory(self):
        with self.assertRaisesRegex(TemplateError, 'outside the views directory'):
            render_template('../README.md')


class ViewRouteTests(unittest.TestCase):
    def setUp(self):
        index.app.config['TESTING'] = True
        self.client = index.app.test_client()

    def test_view_routes_render(self):
        for path in ('/start', '/artist', '/library'):
            with self.subTest(path=path):
                response = self.client.get(path)
                self.assertEqual(response.status_code, 200)
                if path == '/start':
                    self.assertIn(b'Current time is ', response.data)
                    self.assertNotIn(b'${now}', response.data)

    def test_http_error_uses_lua_template_and_keeps_status(self):
        response = self.client.get('/not-found')
        self.assertEqual(response.status_code, 404)
        self.assertEqual(response.content_type, 'text/html')
        self.assertIn(b'Error in template application', response.data)


if __name__ == '__main__':
    unittest.main()
