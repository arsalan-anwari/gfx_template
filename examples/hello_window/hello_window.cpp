import gfx_context;

int main() {

    auto opengl_ctx = gfx_context<gfx_api::opengl>(720, 1080, "Hello Window");

    return 0;
}
